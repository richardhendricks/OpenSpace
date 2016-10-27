/*****************************************************************************************
*                                                                                       *
* OpenSpace                                                                             *
*                                                                                       *
* Copyright (c) 2014-2016                                                               *
*                                                                                       *
* Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
* software and associated documentation files (the "Software"), to deal in the Software *
* without restriction, including without limitation the rights to use, copy, modify,    *
* merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
* permit persons to whom the Software is furnished to do so, subject to the following   *
* conditions:                                                                           *
*                                                                                       *
* The above copyright notice and this permission notice shall be included in all copies *
* or substantial portions of the Software.                                              *
*                                                                                       *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
* PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
* CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
* OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
****************************************************************************************/

#ifndef __CHUNKED_LOD_GLOBE__
#define __CHUNKED_LOD_GLOBE__

#include <memory>

#include <ghoul/logging/logmanager.h>

// open space includes
#include <openspace/rendering/renderengine.h>
#include <openspace/rendering/renderable.h>
#include <openspace/properties/stringproperty.h>
#include <openspace/util/updatestructures.h>

#include <modules/globebrowsing/geometry/ellipsoid.h>
#include <modules/globebrowsing/chunk/chunknode.h>
#include <modules/globebrowsing/tile/tileprovider/tileprovider.h>
#include <modules/globebrowsing/rendering/chunkrenderer.h>
#include <modules/globebrowsing/other/statscollector.h>

namespace openspace {
namespace globebrowsing {

    class ChunkLevelEvaluator;
    class RenderableGlobe;

    class ChunkedLodGlobe : public Renderable {
    public:
        ChunkedLodGlobe(
            const RenderableGlobe& owner,
            size_t segmentsPerPatch,
            std::shared_ptr<LayerManager> layerManager);
        virtual ~ChunkedLodGlobe();

        bool initialize() override;
        bool deinitialize() override;
        bool isReady() const override;

        void render(const RenderData& data) override;
        void update(const UpdateData& data) override;

        /**
         * Traverse the chunk tree and find the highest level chunk node.
         *
         * \param location is given in geodetic coordinates and must be in the range
         * latitude [-90. 90] and longitude [-180, 180]. In other words, it must be a
         * position defined on the globe in georeferenced coordinates.
        */
        const ChunkNode& findChunkNode(const Geodetic2 location) const;

        /**
         * Test if a specific chunk can saefely be culled without affecting the rendered
         * image.
         *
         * Goes through all available <code>ChunkCuller</code>s and check if any of them
         * allows culling of the <code>Chunk</code>s in question.
        */
        bool testIfCullable(const Chunk& chunk, const RenderData& renderData) const;

        /**
         * Gets the desired level which can be used to determine if a chunk should split
         * or merge.
         *
         * Using <code>ChunkLevelEvaluator</code>s, the desired level can be higher or
         * lower than the current level of the <code>Chunks</code>s
         * <code>TileIndex</code>. If the desired level is higher than that of the
         * <code>Chunk</code>, it wants to split. If it is lower, it wants to merge with
         * its siblings. 
        */
        int getDesiredLevel(const Chunk& chunk, const RenderData& renderData) const;
        
        /**
         * Calculates the height from the surface of the reference ellipsoid to the
         * heigh mapped surface.
         *
         * The height can be negative if the height map contains negative values.
         *
         * \param <code>position</code> is the position of a point that gets geodetically
         * projected on the reference ellipsoid. <code>position</code> must be in
         * cartesian model space.
         * \returns the height from the reference ellipsoid to the globe surface.
        */
        float getHeight(glm::dvec3 position) const;

        const int minSplitDepth;
        const int maxSplitDepth;

        std::shared_ptr<LayerManager> layerManager() const;

        StatsCollector stats;
    
    private:
        void debugRenderChunk(const Chunk& chunk, const glm::dmat4& data) const;

        static const GeodeticPatch COVERAGE;
        static const TileIndex LEFT_HEMISPHERE_INDEX;
        static const TileIndex RIGHT_HEMISPHERE_INDEX;

        // Covers all negative longitudes
        std::unique_ptr<ChunkNode> _leftRoot;

        // Covers all positive longitudes
        std::unique_ptr<ChunkNode> _rightRoot;

        // the patch used for actual rendering
        std::unique_ptr<ChunkRenderer> _renderer;

        std::vector<std::unique_ptr<ChunkCuller>> _chunkCullers;

        std::unique_ptr<ChunkLevelEvaluator> _chunkEvaluatorByAvailableTiles;
        std::unique_ptr<ChunkLevelEvaluator> _chunkEvaluatorByProjectedArea;
        std::unique_ptr<ChunkLevelEvaluator> _chunkEvaluatorByDistance;

        std::shared_ptr<LayerManager> _layerManager;

        const RenderableGlobe& _owner;
    };

} // namespace globebrowsing
} // namespace openspace

#endif  // __CHUNKED_LOD_GLOBE__
