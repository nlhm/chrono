// =============================================================================
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2014 projectchrono.org
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file at the top level of the distribution and at
// http://projectchrono.org/license-chrono.txt.
//
// =============================================================================
// Authors: Radu Serban
// =============================================================================
//
// Base class for a single track wheel (template definition).
// A single track wheel is of type LATERAL_PIN.
//
// =============================================================================

#include "chrono/core/ChGlobal.h"
#include "chrono/assets/ChVisualShapeCylinder.h"
#include "chrono/assets/ChTexture.h"

#include "chrono_vehicle/ChSubsysDefs.h"
#include "chrono_vehicle/tracked_vehicle/track_wheel/ChSingleTrackWheel.h"
#include "chrono_vehicle/tracked_vehicle/ChTrackAssembly.h"

namespace chrono {
namespace vehicle {

ChSingleTrackWheel::ChSingleTrackWheel(const std::string& name) : ChTrackWheel(name) {}

void ChSingleTrackWheel::Initialize(std::shared_ptr<ChChassis> chassis,
                                    std::shared_ptr<ChBody> carrier,
                                    const ChVector<>& location,
                                    ChTrackAssembly* track) {
    // Invoke the base class method
    ChTrackWheel::Initialize(chassis, carrier, location, track);

    CreateContactMaterial(m_wheel->GetSystem()->GetContactMethod());
    assert(m_material && m_material->GetContactMethod() == m_wheel->GetSystem()->GetContactMethod());

    // Add contact geometry
    double radius = GetRadius();
    double width = GetWidth();

    m_wheel->SetCollide(true);

    m_wheel->GetCollisionModel()->ClearModel();

    if (track->IsRoadwheelCylinder()) {
        m_wheel->GetCollisionModel()->AddCylinder(m_material, radius, width, VNULL, Q_from_AngX(CH_C_PI_2));
    } else {
        m_wheel->GetCollisionModel()->AddCylindricalShell(m_material, radius, width, VNULL, Q_from_AngX(CH_C_PI_2));
    }

    m_wheel->GetCollisionModel()->BuildModel();
}

void ChSingleTrackWheel::AddVisualizationAssets(VisualizationType vis) {
    if (vis == VisualizationType::NONE)
        return;

    double radius = GetRadius();
    double width = GetWidth();

    ChVehicleGeometry::AddVisualizationCylinder(m_wheel,                       //
                                                ChVector<>(0, width / 2, 0),   //
                                                ChVector<>(0, -width / 2, 0),  //
                                                radius);
}

void ChSingleTrackWheel::RemoveVisualizationAssets() {
    ChPart::RemoveVisualizationAssets(m_wheel);
}

}  // end namespace vehicle
}  // end namespace chrono
