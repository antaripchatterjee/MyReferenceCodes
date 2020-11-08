'''
I refered this video from youtube
https://www.youtube.com/watch?v=6IV_FYx6MQA
'''

class SingletonClass(object):
    __instance = None
    def __new__(cls):
        if self.__instance is None:
            self.__instance = super(SingletonClass, cls).__new__(cls)
            self.v = 10
        return self.__instance

o1 = SingletonClass()
print(o1.v) # prints 10
o1.v = 20
o2 = SingletonClass()
print(o2.v) # prints 20
