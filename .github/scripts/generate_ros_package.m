% generate_ros_package.m (CI-safe deterministic version)

try
    %% -----------------------------
    % Headless / CI-safe mode
    %% -----------------------------
    set(0,'DefaultFigureVisible','off');
    % feature('ShowFigureWindows',0);
    warning('off','all');

    %% -----------------------------
    % Resolve repository root
    %% -----------------------------
    root = getenv('REPO_ROOT');
    if isempty(root)
        root = pwd;
    end

    modelName = 'controller';
    modelPath = fullfile(root, [modelName '.slx']);

    if ~isfile(modelPath)
        error('Model file not found: %s', modelPath);
    end

    %% -----------------------------
    % Copy model into isolated build directory
    %% -----------------------------
    workDir = fullfile(root, 'ros_workdir');
    if ~exist(workDir,'dir')
        mkdir(workDir);
    end

    buildModelPath = fullfile(workDir, [modelName '.slx']);

    fprintf('Copying model to isolated build dir: %s\n', workDir);
    copyfile(modelPath, buildModelPath);

    %% -----------------------------
    % Load ONLY copied model (avoid shadowing)
    %% -----------------------------
    bdclose('all');
    load_system(buildModelPath);

    %% -----------------------------
    % Get configuration set safely
    %% -----------------------------
    cs = getActiveConfigSet(modelName);

    % Force deterministic, non-interactive codegen
    set_param(cs,'SystemTargetFile','ert.tlc');
    set_param(cs,'SolverType','Fixed-step');
    set_param(cs,'StopTime','inf');
    set_param(cs,'LaunchReport','off');
    % set_param(cs,'ModelReferenceTargetType','NONE');

    % Prevent GUI/config prompts
    set_param(0,'DefaultModelBehavior','NonInteractive');

    % Force update to initialize everything deterministically
    set_param(modelName,'SimulationCommand','update');

    %% -----------------------------
    % Build (CI-safe)
    %% -----------------------------
    fprintf('Starting non-interactive build...\n');

    slbuild(modelName);

    fprintf('Build completed successfully.\n');

    %% -----------------------------
    % Collect artifacts
    %% -----------------------------
    outDir = fullfile(root, 'ros_pkg');
    if ~exist(outDir,'dir')
        mkdir(outDir);
    end

    tgzFiles = dir(fullfile(workDir,'**','*.tgz'));
    shFiles  = dir(fullfile(workDir,'**','build_ros_model.sh'));

    for k = 1:numel(tgzFiles)
        src = fullfile(tgzFiles(k).folder, tgzFiles(k).name);
        copyfile(src, outDir);
        fprintf('Copied: %s\n', tgzFiles(k).name);
    end

    for k = 1:numel(shFiles)
        src = fullfile(shFiles(k).folder, shFiles(k).name);
        copyfile(src, fullfile(outDir,'build_ros_model.sh'));
        fprintf('Copied build script.\n');
    end

    if isempty(tgzFiles) && isempty(shFiles)
        fprintf('\nWARNING: No ROS artifacts found.\n');
        fprintf('Check model ROS deployment configuration.\n');
    else
        fprintf('Artifacts written to: %s\n', outDir);
    end

    %% -----------------------------
    % Marker folder for CI
    %% -----------------------------
    markerDir = fullfile(root,'ros_package_artifacts');
    if ~exist(markerDir,'dir')
        mkdir(markerDir);
    end

    fprintf('Done. Marker folder created: %s\n', markerDir);

    bdclose('all');

catch ME
    fprintf('\n=== FULL ERROR REPORT ===\n');
    fprintf('%s\n', getReport(ME,'extended','hyperlinks','off'));
    bdclose('all');
    error(ME.message);
end

exit;