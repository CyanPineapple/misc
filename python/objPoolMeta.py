"""
How to initialize the pool

TEST:
1. The inner
2. The multi use

TODO:
_instances real implmentation
"""
class ObjInPool:
    def __init__(self):
       pass 



class ObjectPool(type):
    _instances = {}
    
    def __call__(cls, *args, **kwargs):
        if cls not in cls._instances:
            cls._instances[cls] = []
            for i in range(3):
                iniobj = super(ObjectPool, cls).__call__(*args, **kwargs)
                cls._instances[cls].append(iniobj) 

            return cls._instances[cls].pop()

        if cls._instances[cls]:
            return cls._instances[cls].pop()
        else:
            return None



class BatsObj(metaclass=ObjectPool):

    def __init__(self):
        print("Object Generated!")

    def __del__(self):
        if self:
            self.__class__._instances[self.__class__].append(self)
            print("Object Released!")
        else:
            print("The object is None, nothing to release")



if __name__=="__main__":
    print("Testing")
    obj1 = BatsObj()
    obj2 = BatsObj()
    obj3 = BatsObj()
