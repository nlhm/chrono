// =============================================================================
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2014 projectchrono.org
// All right reserved.
//
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file at the top level of the distribution and at
// http://projectchrono.org/license-chrono.txt.
//
// =============================================================================
// Authors: Radu Serban, Asher Elmquist, Jayne Henry
// =============================================================================
//
// Wrapper classes for modeling an entire RCCar vehicle assembly
// (including the vehicle itself, the powertrain, and the tires).
//
// =============================================================================

#ifndef RCCAR_H
#define RCCAR_H

#include <array>
#include <string>

#include "chrono_vehicle/wheeled_vehicle/tire/ChPacejkaTire.h"

// #include "chrono_models/ChApiModels.h"
#include "chrono_models/vehicle/rccar/RCCar_Vehicle.h"
#include "chrono_models/vehicle/rccar/RCCar_SimpleMapPowertrain.h"
#include "chrono_models/vehicle/rccar/RCCar_RigidTire.h"
#include "chrono_models/vehicle/rccar/RCCar_TMeasyTire.h"

using namespace chrono;
using namespace chrono::vehicle;

namespace chrono {
namespace vehicle {
namespace rccar {

/// @addtogroup vehicle_models_rccar
/// @{

/// Definition of the RCCar assembly.
/// This class encapsulates a concrete wheeled vehicle model with parameters corresponding to
/// a RC car, the powertrain model, and the 4 tires. It provides wrappers to access the different
/// systems and subsystems, functions for specifying the tire types, as well as functions for
/// controlling the visualization mode of each component.
class CH_MODELS_API RCCar {
  public:
    RCCar();
    RCCar(ChSystem* system);

    ~RCCar();

    void SetContactMethod(ChContactMethod val) { m_contactMethod = val; }

    void SetChassisFixed(bool val) { m_fixed = val; }
    void SetChassisCollisionType(CollisionType val) { m_chassisCollisionType = val; }

    void SetTireType(TireModelType val) { m_tireType = val; }

    void SetInitPosition(const ChCoordsys<>& pos) { m_initPos = pos; }
    void SetInitFwdVel(double fwdVel) { m_initFwdVel = fwdVel; }
    void SetInitWheelAngVel(const std::vector<double>& omega) { m_initOmega = omega; }

    void SetTireStepSize(double step_size) { m_tire_step_size = step_size; }

    ChSystem* GetSystem() const { return m_vehicle->GetSystem(); }
    ChWheeledVehicle& GetVehicle() const { return *m_vehicle; }
    std::shared_ptr<ChChassis> GetChassis() const { return m_vehicle->GetChassis(); }
    std::shared_ptr<ChBodyAuxRef> GetChassisBody() const { return m_vehicle->GetChassisBody(); }
    std::shared_ptr<ChPowertrain> GetPowertrain() const { return m_vehicle->GetPowertrain(); }

    void Initialize();

    void LockAxleDifferential(int axle, bool lock) { m_vehicle->LockAxleDifferential(axle, lock); }

    void SetAerodynamicDrag(double Cd, double area, double air_density);

    void SetChassisVisualizationType(VisualizationType vis) { m_vehicle->SetChassisVisualizationType(vis); }
    void SetSuspensionVisualizationType(VisualizationType vis) { m_vehicle->SetSuspensionVisualizationType(vis); }
    void SetSteeringVisualizationType(VisualizationType vis) { m_vehicle->SetSteeringVisualizationType(vis); }
    void SetWheelVisualizationType(VisualizationType vis) { m_vehicle->SetWheelVisualizationType(vis); }
    void SetTireVisualizationType(VisualizationType vis) { m_vehicle->SetTireVisualizationType(vis); }

    /// Set parameters for tuning engine map.
    void SetMaxMotorVoltageRatio(double voltage_ratio) { m_voltage_ratio = voltage_ratio; }

    /// Set stall torque.
    void SetStallTorque(double stall_torque) { m_stall_torque = stall_torque; }

    /// Set tire rolling friction coefficient.
    void SetTireRollingResistance(double rolling_resistance) { m_rolling_friction_coeff = rolling_resistance; }
    
    /// Set coefficients for motor resistance torque.
    void SetMotorResistanceCoefficients(double c0, double c1) {
        m_motor_resistance_c0 = c0;
        m_motor_resistance_c1 = c1;
    }

    void Synchronize(double time, const DriverInputs& driver_inputs, const ChTerrain& terrain);
    void Advance(double step);

    void LogHardpointLocations() { m_vehicle->LogHardpointLocations(); }
    void DebugLog(int what) { m_vehicle->DebugLog(what); }

  protected:
    ChContactMethod m_contactMethod;
    CollisionType m_chassisCollisionType;
    bool m_fixed;

    TireModelType m_tireType;

    double m_tire_step_size;

    ChCoordsys<> m_initPos;
    double m_initFwdVel;
    std::vector<double> m_initOmega;

    bool m_apply_drag;
    double m_Cd;
    double m_area;
    double m_air_density;

    ChSystem* m_system;
    RCCar_Vehicle* m_vehicle;

    double m_tire_mass;

    double m_stall_torque;
    double m_voltage_ratio;
    double m_rolling_friction_coeff;
    double m_motor_resistance_c0;
    double m_motor_resistance_c1;
};

/// @} vehicle_models_rccar

}  // namespace rccar
}  // namespace vehicle
}  // namespace chrono

#endif
