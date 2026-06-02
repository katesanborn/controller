% Auto-generated skeleton: generate_ros_package.m
% Opens the Simulink model and attempts to build/generate a ROS package.
% Replace the placeholder generation call with the exact programmatic API
% you use in MATLAB (the UI "Deploy > Generate ROS Package" maps to a
% specific code-generation API for ROS in your MATLAB release).

try
    root = pwd;
    modelName = 'controller';
    modelFile = fullfile(root, [modelName '.slx']);

    // fprintf('Starting ROS master (rosinit)...\n');
    // try
    //     rosinit;
    // catch rosErr
    //     fprintf('rosinit error or ROS already running: %s\n', rosErr.message);
    // end

    % Use a temporary writable working folder for code generation
    workDir = fullfile(root, 'ros_workdir');
    if ~exist(workDir,'dir')
        mkdir(workDir);
    end

    fprintf('Copying model to workdir: %s\n', workDir);
    copyModelFile = fullfile(workDir, [modelName '.slx']);
    copyfile(modelFile, copyModelFile);

    fprintf('Opening model copy %s...\n', copyModelFile);
    load_system(copyModelFile);

    // % Configure basic solver and codegen-friendly settings (per MathWorks doc)
    // fprintf('Configuring model solver for code generation...\n');
    // try
    //     set_param(modelName, 'SolverType', 'Fixed-step');
    //     set_param(modelName, 'Solver', 'ode3');
    //     set_param(modelName, 'FixedStep', '0.05');
    // catch cfgErr
    //     fprintf('Warning: Could not set one or more config params: %s\n', cfgErr.message);
    // end

    try
        set_param(modelName,'SimulationCommand','update');
    catch ME
        disp(getReport(ME,'extended'));
    end

    fprintf('Attempting to build model with slbuild (this generates the ROS package artifacts)...\n');
    try
        slbuild(modelName);
    catch ME
        disp(getReport(ME,'extended'));
        rethrow(ME);
    end

    % Look for generated artifacts per the MathWorks workflow
    outDir = fullfile(root, 'ros_pkg');
    if ~exist(outDir,'dir')
        mkdir(outDir);
    end

    % slbuild typically writes the .tgz and build_ros_model.sh into the current folder
    % Search the working directory for those artifacts and copy them to outDir
    tgzFiles = dir(fullfile(workDir, '*.tgz'));
    shFile = fullfile(workDir, 'build_ros_model.sh');
    if ~isempty(tgzFiles)
        for k=1:numel(tgzFiles)
            src = fullfile(workDir, tgzFiles(k).name);
            dest = fullfile(outDir, tgzFiles(k).name);
            copyfile(src,dest);
            fprintf('Copied %s -> %s\n', src, dest);
        end
    else
        fprintf('No .tgz artifacts found in workdir (%s).\n', workDir);
    end

    if exist(shFile,'file')==2
        copyfile(shFile, fullfile(outDir, 'build_ros_model.sh'));
        fprintf('Copied build script to %s\n', outDir);
    else
        fprintf('No build_ros_model.sh found in workdir (%s).\n', workDir);
    end

    if isempty(tgzFiles) && exist(shFile,'file')~=2
        fprintf('\nNo ROS-package artifacts found. If the ROS app settings (Deploy Type etc.) were not configured,\n');
        fprintf('open the model in MATLAB, use the ROS app (Apps > Robot Operating System > ROS), set:\n');
        fprintf('- Prepare -> Hardware Settings (maintainer/package metadata)\n');
        fprintf('- ROS tab -> Deploy Type = "Standard Node"\n');
        fprintf('Then press Deploy -> Build Model once interactively; this should produce the .tgz and build script.\n');
    else
        fprintf('Artifacts collected in: %s\n', outDir);
    end

    % Create a marker output folder so the workflow can pick up artifacts
    outDir = fullfile(root, 'ros_package_artifacts');
    if ~exist(outDir, 'dir')
        mkdir(outDir);
    end
    fprintf('Generation script finished. Place generated package into: %s\n', outDir);

catch ME
    fprintf('Error in generate_ros_package.m: %s\n', ME.message);
end

exit;