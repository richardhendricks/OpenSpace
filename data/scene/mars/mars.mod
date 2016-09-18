return {
    -- Mars barycenter module
    {
        Name = "MarsBarycenter",
        Parent = "SolarSystemBarycenter",
        -- Scene Radius in KM:
        SceneRadius = 1.0E+5,        
        -- Ephemeris = {
        --     Type = "Static"
        -- }
        Ephemeris = {
            Type = "Spice",
            Body = "MARS BARYCENTER",
            Reference = "ECLIPJ2000",
            Observer = "SUN",
            Kernels = {
                "${OPENSPACE_DATA}/spice/de430_1850-2150.bsp"
            }
        },
    },

    -- Mars module
    {   
        Name = "Mars",
        Parent = "MarsBarycenter",
        -- Scene Radius in KM:
        SceneRadius = 5.0E+4,
        Renderable = {
            Type = "RenderablePlanet",
            Frame = "IAU_MARS",
            Body = "MARS BARYCENTER",
            Geometry = {
                Type = "SimpleSphere",
                Radius = { 3.3895, 6 },
                Segments = 100
            },
            Textures = {
                Type = "simple",
                Color = "textures/mars.jpg",
            },
        },
        -- Ephemeris = {
        --     Type = "Spice",
        --     Body = "MARS BARYCENTER",
        --     Reference = "ECLIPJ2000",
        --     Observer = "SUN",
        --     Kernels = {
        --        "${OPENSPACE_DATA}/spice/de430_1850-2150.bsp"
        --    }
        -- },
        Rotation = {
            Type = "Spice",
            Frame = "IAU_MARS",
            Reference = "ECLIPJ2000"
        },
        GuiName = "/Solar/Planets/Mars"
    },
    -- MarsTrail module
    {   
        Name = "MarsTrail",
        --Parent = "MarsBarycenter",
        Parent = "SolarSystemBarycenter",
        Renderable = {
            Type = "RenderableTrail",
            Body = "MARS BARYCENTER",
            Frame = "GALACTIC",
            Observer = "SUN",
            RGB = { 1, 0.8, 0.5 },
            TropicalOrbitPeriod = 686.973,
            EarthOrbitRatio = 1.881,
            DayLength = 24.6597,
            Textures = {
                Type = "simple",
                Color = "${COMMON_MODULE}/textures/glare_blue.png",
                -- need to add different texture
            },  
        },
        GuiName = "/Solar/MarsTrail"
    }
}
