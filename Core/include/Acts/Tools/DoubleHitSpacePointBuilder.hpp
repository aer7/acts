// This file is part of the Acts project.
//
// Copyright (C) 2018 Acts project team
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "Acts/Digitization/CartesianSegmentation.hpp"
#include "Acts/Digitization/DigitizationModule.hpp"
#include "Acts/Tools/ISpacePointBuilder.hpp"
#include "Acts/Tools/SingleHitSpacePointBuilder.hpp"
#include "Acts/Utilities/Units.hpp"

namespace Acts {

/// @brief Structure for easier bookkeeping of clusters.
struct DoubleHitSpacePoint
{
  /// Storage of the hit cluster on a surface
  PlanarModuleCluster const* clusterFront;
  /// Storage of the hit cluster on another surface
  PlanarModuleCluster const* clusterBack;
  /// Storage of a space point. Zero vector indicates unset point
  Vector3D spacePoint = {0., 0., 0.};
};

/// @brief Configuration of the class to steer its behaviour
struct DoubleHitSpacePointConfig
{
  /// Accepted difference in eta for two clusters
  double diffTheta2 = 1.;
  /// Accepted difference in phi for two clusters
  double diffPhi2 = 1.;
  /// Accepted distance between two clusters
  double diffDist = 100. * units::_mm;
  /// Allowed increase of strip length
  double stripLengthTolerance = 0.01;
  /// Allowed increase of strip length wrt gaps between strips
  double stripLengthGapTolerance = 0.01;
  /// Assumed position of the vertex
  Vector3D vertex = {0., 0., 0.};
  /// Perform the perpendicular projection for space point finding
  bool usePerpProj = false;
};

/// @class TwoHitsSpacePointBuilder
///
/// After the particle interaction with surfaces are recorded and digitized
/// the hits strip detectors need further treatment. This class takes
/// the digitized clusters and combines them on two different detector elements
/// to a
/// result of the combined detector element. The class is intended to handle
/// strip detector elements in particular.
///
/// @note Used abbreviation: "Strip Detector Element" -> SDE
///
template <>
class SpacePointBuilder<DoubleHitSpacePoint, DoubleHitSpacePointConfig>
    : public SpacePointBuilder<SingleHitSpacePoint, void>
{
public:
  /// Default constructor
  SpacePointBuilder<DoubleHitSpacePoint, DoubleHitSpacePointConfig>() = delete;

  /// @brief This function is intended to use a single cluster for the formation
  /// of
  /// a space point. Since this is not needed for this class this function is
  /// deleted.
  static void
  addClusters(std::vector<DoubleHitSpacePoint>&              spacePointStorage,
              const std::vector<PlanarModuleCluster const*>& hits)
      = delete;

  /// @brief Searches possible combinations of two clusters on different
  /// surfaces
  /// that may come from the same particles
  /// @param spacePointStorage storage of the space points
  /// @param clustersFront vector of clusters on a surface
  /// @param clustersBack vector of clusters on another surface
  /// @param cfg optional configuration to steer the combination process of @p
  /// clustersFront and @p clustersBack
  /// @note The structure of @p clustersFront and @p clustersBack is meant to be
  /// clusters[Independent clusters on a single surface]
  static void
  addClusters(std::vector<DoubleHitSpacePoint>&              spacePointStorage,
              const std::vector<PlanarModuleCluster const*>& clustersFront,
              const std::vector<PlanarModuleCluster const*>& clustersBack,
              const std::shared_ptr<DoubleHitSpacePointConfig> cfg = nullptr);

  /// @brief Calculates the space points out of a given collection of clusters
  /// on several strip detectors and stores the data
  /// @param spacePointStorage storage of the data
  /// @param cfg optional configuration to steer the calculation of the space
  /// points
  /// @note If no configuration is set, the default values will be used
  static void
  calculateSpacePoints(std::vector<DoubleHitSpacePoint>& spacePoints,
                       const std::shared_ptr<DoubleHitSpacePointConfig> cfg
                       = nullptr);

private:
  /// @brief Storage container for variables related to the calculation of space
  /// points
  struct SpacePointParameters
  {
    /// Vector pointing from bottom to top end of first SDE
    Vector3D q;
    /// Vector pointing from bottom to top end of second SDE
    Vector3D r;
    /// Twice the vector pointing from vertex to to midpoint of first SDE
    Vector3D s;
    /// Twice the vector pointing from vertex to to midpoint of second SDE
    Vector3D t;
    /// Cross product between SpacePointParameters::q and
    /// SpacePointParameters::s
    Vector3D qs;
    /// Cross product between SpacePointParameters::r and
    /// SpacePointParameters::t
    Vector3D rt;
    /// Magnitude of SpacePointParameters::q
    double qmag = 0.;
    /// Parameter that determines the hit position on the first SDE
    double m = 0.;
    /// Parameter that determines the hit position on the second SDE
    double n = 0.;
    /// Regular limit of the absolut values of SpacePointParameters::m and
    /// SpacePointParameters::n
    double limit = 1.;
    /// Limit of SpacePointParameters::m and SpacePointParameters::n in case of
    /// variable vertex
    double limitExtended = 1.;

    /// @brief reset structure and allows to reuse the same structure
    void
    reset()
    {
      // Set every vector to nullvector. This allows checks, if a variable was
      // already set.
      q  = {0., 0., 0.};
      r  = {0., 0., 0.};
      s  = {0., 0., 0.};
      t  = {0., 0., 0.};
      qs = {0., 0., 0.};
      rt = {0., 0., 0.};
      // Set every double to default values
      qmag          = 0;
      m             = 0;
      n             = 0;
      limit         = 1.;
      limitExtended = 1.;
    }
  };

  /// @brief Calculates (Delta theta)^2 + (Delta phi)^2 between two clusters
  /// @param pos1 position of the first cluster
  /// @param pos2 position the second cluster
  /// @param cfg optional configuration to steer the combination process of @p
  /// pos1 and @p pos2
  /// @return the squared sum in case of success, otherwise -1
  static double
  differenceOfClusters(const Vector3D&                                  pos1,
                       const Vector3D&                                  pos2,
                       const std::shared_ptr<DoubleHitSpacePointConfig> cfg);

  /// @brief Calculates the top and bottom ends of a SDE
  /// that corresponds to a given hit
  /// @param cluster object that stores the information about the hit
  /// @return vectors to the top and bottom end of the SDE
  static std::pair<Vector3D, Vector3D>
  endsOfStrip(const PlanarModuleCluster& cluster);

  /// @brief Calculates a space point whithout using the vertex
  /// @note This is mostly to resolve space points from cosmic data
  /// @param a vector to the top end of the first SDE
  /// @param c vector to the top end of the second SDE
  /// @param q vector from the bottom to the top end of the first SDE
  /// @param r vector from the bottom to the top end of the second SDE
  /// @return parameter that indicates the location of the space point; returns
  /// 1. if it failed
  /// @note The meaning of the parameter is explained in more detail in the
  /// function body
  static double
  calcPerpProj(const Vector3D& a,
               const Vector3D& c,
               const Vector3D& q,
               const Vector3D& r);

  /// @brief This function tests if a space point can be estimated by a more
  /// tolerant treatment of construction. In fact, this function indirectly
  /// allows shifts of the vertex.
  /// @param spaPoPa container that stores geometric parameters and rules of the
  /// space point formation
  /// @param cfg optional configuration to steer the recovery of space points
  /// @return indicator if the test was successful
  static bool
  recoverSpacePoint(SpacePointParameters&                            spaPoPa,
                    const std::shared_ptr<DoubleHitSpacePointConfig> cfg);
};

}  // namespace Acts
