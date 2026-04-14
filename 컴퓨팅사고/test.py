str = "12시 25분 3초"
flag = True
for i in str:
        
    if i >= '1' and i <= '9':
        print(i, end = '')
    elif flag == False:
        print(':', end = '')
        flag = True
    else :
        flag = False
    
    