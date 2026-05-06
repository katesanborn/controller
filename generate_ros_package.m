% Auto-generated skeleton: generate_ros_package.m
% Opens the Simulink model and attempts to build/generate a ROS package.
% Replace the placeholder generation call with the exact programmatic API
% you use in MATLAB (the UI "Deploy > Generate ROS Package" maps to a
% specific code-generation API for ROS in your MATLAB release).

try
    root = pwd;
    modelName = 'controller';
    modelFile = fullfile(root, [modelName '.slx']);

    fprintf('Attempting to build model with slbuild (this generates the ROS package artifacts)...\n');
    try
        slbuild(modelName);
    catch buildErr
        fprintf('slbuild failed or is not applicable: %s\n', buildErr.message);
    end

catch ME
    fprintf('Error in generate_ros_package.m: %s\n', ME.message);
end

exit;
