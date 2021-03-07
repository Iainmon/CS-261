
data Color = Color { red :: Double
                   , green :: Double
                   , blue :: Double
                   } deriving (Eq)

data Location = UV Double Double

glslColor c = "vec3(" ++ (show (red c)) ++ ", " ++ (show (green c)) ++ ", " ++ (show (blue c)) ++ ")"

data Layer = Base Color | Combination (Location -> Double) Layer Layer

composeDistanceField :: (Location -> Double) -> Double -> Double -> (Location -> Double)
composeDistanceField f b s = hlerp 
main = print $ glslColor $ Color { red = 1.0, green = 0.8, blue = 0.2 }

