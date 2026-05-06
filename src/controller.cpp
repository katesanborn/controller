//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller.cpp
//
// Code generated for Simulink model 'controller'.
//
// Model version                  : 1.44
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Wed May  6 10:57:06 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "controller.h"
#include "rtwtypes.h"
#include "controller_types.h"

// Block signals (default storage)
B_controller_T controller_B;

// Block states (default storage)
DW_controller_T controller_DW;

// Real-time model
RT_MODEL_controller_T controller_M_ = RT_MODEL_controller_T();
RT_MODEL_controller_T *const controller_M = &controller_M_;

// Model step function
void controller_step(void)
{
  SL_Bus_controller_std_msgs_Float64 rtb_BusAssignment1;
  SL_Bus_controller_std_msgs_Float64 rtb_SourceBlock_o2_p_0;
  real_T u0;
  boolean_T b_varargout_1;

  // Outputs for Atomic SubSystem: '<Root>/Subscribe'
  // MATLABSystem: '<S3>/SourceBlock'
  b_varargout_1 = Sub_controller_52.getLatestMessage(&rtb_SourceBlock_o2_p_0);

  // Outputs for Enabled SubSystem: '<S3>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S7>/Enable'

  // Start for MATLABSystem: '<S3>/SourceBlock'
  if (b_varargout_1) {
    // SignalConversion generated from: '<S7>/In1'
    controller_B.In1_bg = rtb_SourceBlock_o2_p_0;
  }

  // End of Start for MATLABSystem: '<S3>/SourceBlock'
  // End of Outputs for SubSystem: '<S3>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<Root>/Subscribe'

  // Outputs for Atomic SubSystem: '<Root>/Subscribe1'
  // MATLABSystem: '<S4>/SourceBlock'
  b_varargout_1 = Sub_controller_53.getLatestMessage(&rtb_SourceBlock_o2_p_0);

  // Outputs for Enabled SubSystem: '<S4>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S8>/Enable'

  // Start for MATLABSystem: '<S4>/SourceBlock'
  if (b_varargout_1) {
    // SignalConversion generated from: '<S8>/In1'
    controller_B.In1_b = rtb_SourceBlock_o2_p_0;
  }

  // End of Start for MATLABSystem: '<S4>/SourceBlock'
  // End of Outputs for SubSystem: '<S4>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<Root>/Subscribe1'

  // Outputs for Atomic SubSystem: '<Root>/Subscribe4'
  // MATLABSystem: '<S5>/SourceBlock'
  b_varargout_1 = Sub_controller_54.getLatestMessage(&rtb_SourceBlock_o2_p_0);

  // Outputs for Enabled SubSystem: '<S5>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S9>/Enable'

  // Start for MATLABSystem: '<S5>/SourceBlock'
  if (b_varargout_1) {
    // SignalConversion generated from: '<S9>/In1'
    controller_B.In1 = rtb_SourceBlock_o2_p_0;
  }

  // End of Start for MATLABSystem: '<S5>/SourceBlock'
  // End of Outputs for SubSystem: '<S5>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<Root>/Subscribe4'

  // Product: '<S6>/Product2' incorporates:
  //   Constant: '<S6>/d_min'
  //   Constant: '<S6>/k'
  //   Constant: '<S6>/t_min'
  //   Product: '<S6>/Product'
  //   Product: '<S6>/Product1'
  //   Sum: '<S6>/Minus'
  //   Sum: '<S6>/Plus'
  //   Sum: '<S6>/Plus1'

  u0 = ((controller_B.In1_bg.Data - (2.0 * controller_B.In1_b.Data + 15.0)) *
        0.1 + controller_B.In1.Data) * controller_ConstB.Divide;

  // Saturate: '<Root>/min//max 1.5//-3.0'
  if (u0 > 1.5) {
    // BusAssignment: '<Root>/Bus Assignment1'
    rtb_BusAssignment1.Data = 1.5;
  } else if (u0 < -3.0) {
    // BusAssignment: '<Root>/Bus Assignment1'
    rtb_BusAssignment1.Data = -3.0;
  } else {
    // BusAssignment: '<Root>/Bus Assignment1'
    rtb_BusAssignment1.Data = u0;
  }

  // End of Saturate: '<Root>/min//max 1.5//-3.0'

  // Outputs for Atomic SubSystem: '<Root>/Publish1'
  // MATLABSystem: '<S2>/SinkBlock'
  Pub_controller_49.publish(&rtb_BusAssignment1);

  // End of Outputs for SubSystem: '<Root>/Publish1'
}

// Model initialize function
void controller_initialize(void)
{
  {
    int32_T i;
    char_T b_zeroDelimTopic_0[16];
    char_T b_zeroDelimTopic[10];
    char_T b_zeroDelimTopic_1[8];
    static const char_T b_zeroDelimTopic_2[10] = "lead_dist";
    static const char_T b_zeroDelimTopic_3[10] = "cmd_accel";
    static const char_T b_zeroDelimTopic_4[16] = "car/state/vel_x";
    static const char_T b_zeroDelimTopic_5[8] = "rel_vel";

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe'
    // Start for MATLABSystem: '<S3>/SourceBlock'
    controller_DW.obj_e.matlabCodegenIsDeleted = false;
    controller_DW.obj_e.isInitialized = 1;
    for (i = 0; i < 10; i++) {
      b_zeroDelimTopic[i] = b_zeroDelimTopic_2[i];
    }

    Sub_controller_52.createSubscriber(&b_zeroDelimTopic[0], 1);
    controller_DW.obj_e.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S3>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe'

    // SystemInitialize for Atomic SubSystem: '<Root>/Publish1'
    // Start for MATLABSystem: '<S2>/SinkBlock'
    controller_DW.obj.matlabCodegenIsDeleted = false;
    controller_DW.obj.isInitialized = 1;
    for (i = 0; i < 10; i++) {
      b_zeroDelimTopic[i] = b_zeroDelimTopic_3[i];
    }

    Pub_controller_49.createPublisher(&b_zeroDelimTopic[0], 1);
    controller_DW.obj.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S2>/SinkBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Publish1'

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe1'
    // Start for MATLABSystem: '<S4>/SourceBlock'
    controller_DW.obj_p.matlabCodegenIsDeleted = false;
    controller_DW.obj_p.isInitialized = 1;
    for (i = 0; i < 16; i++) {
      b_zeroDelimTopic_0[i] = b_zeroDelimTopic_4[i];
    }

    Sub_controller_53.createSubscriber(&b_zeroDelimTopic_0[0], 1);
    controller_DW.obj_p.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S4>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe1'

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe4'
    // Start for MATLABSystem: '<S5>/SourceBlock'
    controller_DW.obj_m.matlabCodegenIsDeleted = false;
    controller_DW.obj_m.isInitialized = 1;
    for (i = 0; i < 8; i++) {
      b_zeroDelimTopic_1[i] = b_zeroDelimTopic_5[i];
    }

    Sub_controller_54.createSubscriber(&b_zeroDelimTopic_1[0], 1);
    controller_DW.obj_m.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S5>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe4'
  }
}

// Model terminate function
void controller_terminate(void)
{
  // Terminate for Atomic SubSystem: '<Root>/Subscribe'
  // Terminate for MATLABSystem: '<S3>/SourceBlock'
  if (!controller_DW.obj_e.matlabCodegenIsDeleted) {
    controller_DW.obj_e.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S3>/SourceBlock'
  // End of Terminate for SubSystem: '<Root>/Subscribe'

  // Terminate for Atomic SubSystem: '<Root>/Subscribe1'
  // Terminate for MATLABSystem: '<S4>/SourceBlock'
  if (!controller_DW.obj_p.matlabCodegenIsDeleted) {
    controller_DW.obj_p.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S4>/SourceBlock'
  // End of Terminate for SubSystem: '<Root>/Subscribe1'

  // Terminate for Atomic SubSystem: '<Root>/Subscribe4'
  // Terminate for MATLABSystem: '<S5>/SourceBlock'
  if (!controller_DW.obj_m.matlabCodegenIsDeleted) {
    controller_DW.obj_m.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S5>/SourceBlock'
  // End of Terminate for SubSystem: '<Root>/Subscribe4'

  // Terminate for Atomic SubSystem: '<Root>/Publish1'
  // Terminate for MATLABSystem: '<S2>/SinkBlock'
  if (!controller_DW.obj.matlabCodegenIsDeleted) {
    controller_DW.obj.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S2>/SinkBlock'
  // End of Terminate for SubSystem: '<Root>/Publish1'
}

const char_T* RT_MODEL_controller_T::getErrorStatus() const
{
  return (errorStatus);
}

void RT_MODEL_controller_T::setErrorStatus(const char_T* const volatile
  aErrorStatus)
{
  (errorStatus = aErrorStatus);
}

//
// File trailer for generated code.
//
// [EOF]
//
