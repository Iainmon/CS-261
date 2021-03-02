

data Graph a = Vert a [Graph a] deriving (Show)

numId :: (Num a) => a
numId = fromInteger 1

consStarGraph :: (Num a) => Integer -> a -> Graph a
consStarGraph 0 m = Vert m []
consStarGraph n m = Vert m edges where
    edges = map (\k -> consStarGraph 0 (m + fromInteger k) ) [1..n]

addPoint :: Graph a -> Graph a -> Graph a
addPoint (Vert m edges) point = Vert m (point : edges)

instance Functor Graph where
    -- fmap :: (a -> b) -> F a -> F b
    fmap f (Vert m [])     = Vert (f m) []
    fmap f (Vert m (g:gs)) = Vert (f m) $ map (fmap f) gs


main = print $ fmap (+1) $ consStarGraph 3 0
