import Prelude

-- My (naive) implementation of a dictionary in Haskell
-- I have (no/very little) idea what I'm doing
data Dictionary k v
  = Empty
  | Leaf k
         v
  | Node k
         (Dictionary k v)
         (Dictionary k v)

instance (Show k, Show v) =>
         Show (Dictionary k v) where
  show Empty = "[]"
  show (Leaf k v) = show k ++ " => " ++ show v
  show (Node cutoff left right) = show left ++ ", " ++ show right

instance Functor (Dictionary k) where
  fmap _ Empty = Empty
  fmap f (Leaf k v) = Leaf k (f v)
  fmap f (Node cutoff left right) = Node cutoff (fmap f left) (fmap f right)

insert
  :: (Show k, Show v, Ord k)
  => k -> v -> Dictionary k v -> Dictionary k v
insert k v Empty = Leaf k v
insert k1 v1 (Leaf k2 v2)
  | k1 == k2 = (Leaf k2 v1)
  | k1 < k2 = Node k2 (Leaf k1 v1) (Leaf k2 v2)
  | otherwise = Node k1 (Leaf k2 v2) (Leaf k1 v1)
insert k v (Node cutoff left right) =
  if k < cutoff
    then (Node cutoff (insert k v left) right)
    else (Node k left (insert k v right))

get
  :: (Show k, Show v, Ord k)
  => k -> Dictionary k v -> Maybe v
get _ Empty = Nothing
get k (Leaf k' v) =
  if k == k'
    then Just v
    else Nothing
get k (Node cutoff left right) =
  if k < cutoff
    then get k left
    else get k right

fromList
  :: (Show k, Show v, Ord k)
  => [(k, v)] -> Dictionary k v
fromList [] = Empty
fromList [(k, v)] = Leaf k v
fromList ((k, v):rest) = insert k v $ fromList rest

toList
  :: (Show k, Show v, Ord k)
  => Dictionary k v -> [(k, v)]
toList Empty = []
toList (Leaf k v) = [(k, v)]
toList (Node _ left right) = (toList left) ++ (toList right)
