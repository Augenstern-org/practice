class Dog:
    def __init__(self,n,b,a):
        self.__name = n
        self.__breed = b
        self.__age = a
    
    def get_name(self):
        return self.__name
    
    def act(self):
        print(self.__name,": ",self.__breed,sep="")
    
    def change_breed(self,b):
        self.__breed = b


yy = Dog("yy","你吗",3)
yy.act()
yy.change_breed("唧吧")
yy.act()
