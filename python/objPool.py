class ObjInPool:
    def __init__(self):
       pass 


class BatsObj():
    
    _pool = [ObjInPool() for i in range(10)]

    def __init__(self):
        self.object = None
        if self.__class__._pool:
            self.object = self.__class__._pool.pop()
            print("Generated! Pool size: {}"
                  .format(len(self.__class__._pool)))
        else:
            print("empty pool!")

    def __del__(self):
        if self.object:
            self.__class__._pool.append(self.object)
            print("Released! Pool size: {}"
              .format(len(self.__class__._pool)))
        else:
            print("Nothing to release")


        



if __name__=="__main__":


    print("Start Testing ...")
    objlist = []
    for i in range(11):
        objlist.append(BatsObj())

    
