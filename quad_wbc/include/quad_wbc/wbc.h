//
// Created by qiayuan on 2022/7/1.
//

#pragma once

#include "quad_wbc/ho_qp.h"

#include <ocs2_mpc/SystemObservation.h>
#include <ocs2_legged_robot/LeggedRobotInterface.h>
#include <ocs2_legged_robot/gait/MotionPhaseDefinition.h>

namespace quad_ros
{
using namespace ocs2;
using namespace legged_robot;

// Decision Variables: x = [\dot u^T, F^T, \tau^T]^T
class Wbc
{
public:
  Wbc(LeggedRobotInterface& legged_interface);
  vector_t update(const vector_t& state_desired, const vector_t& input_desired, vector_t& measured_rbd_state,
                  size_t mode);

private:
  Task formulateFloatingBaseEomTask();
  Task formulateTorqueLimitsTask();
  Task formulateContactForceTask(const vector_t& input);
  Task formulateFrictionConeTask(const vector_t& input);

  size_t num_decision_vars_;
  PinocchioInterface& pino_interface_;
  const CentroidalModelInfo& info_;
  contact_flag_t contact_flag_;
  size_t num_contacts_;
};

}  // namespace quad_ros