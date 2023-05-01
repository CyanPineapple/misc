type KnightPos = (Int,Int) 

moveKnight :: KnightPos -> [KnightPos]
moveKnight (c,r) = filter onBoard 
    [(c+2,r-1),(c+2,r+1),(c-2,r-1),(c-2,r+1)
    ,(c+1,r-2),(c+1,r+2),(c-1,r-2),(c-1,r+2)
    ]
    where onBoard (c,r) = c `elem` [1..8] && r `elem` [1..8]

richin3 :: KnightPos -> KnightPos -> Bool
richin3 start end = end `elem` res
    where res = do
            first <- moveKnight start
            second <- moveKnight first
            moveKnight second
    -- res = return start >>= moveKnight >>= moveKnight >>= moveKnight
    