

data Tree a = Leaf a | Branch a (Tree a) (Tree a) | Nil deriving (Show)

type Traversal a = [Tree a]

type Turn a = Tree a -> Maybe (Tree a)

right, left :: Turn a
right (Branch _ _ rhs) = Just rhs
right _ = Nothing 

left (Branch _ lhs _) = Just lhs
left _ = Nothing 

nodeValue :: Tree a -> Maybe a
nodeValue (Leaf x)       = Just x
nodeValue (Branch x _ _) = Just x
nodeValue Nil            = Nothing

access :: Tree a -> [Turn a] -> Maybe a
access Nil _       = Nothing
-- access (Leaf x) [] = Just x
-- access (Branch x _ _) [] = access (Leaf x) []
access node [] = nodeValue node
access node (y:ys) = y node >>= \tr -> access tr ys


testData = Branch 1 (Leaf 2) (Leaf 3)
testPath = [left]
