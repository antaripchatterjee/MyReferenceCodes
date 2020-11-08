'''
I refered this video from youtube
https://www.youtube.com/watch?v=6IV_FYx6MQA
'''
def singleton(cls):
    instances = {}
    def getInstance(*argv, **kwargv):
        if cls not in instances:
            instances[cls] = cls(*argv, **kwargv)
        return instances[cls]
    return getInstance

@singleton
class SingletonClass:
    pass

o1 = SingletonClass()
o2 = SingletonClass()

print(o1 == o2) # prints True