n = int(input())

tmp = list()
i = 2
while(i <= n):
    if n % i == 0:
        tmp.append(i)
        n /= i
    else: 
        i += 1
print(tmp)

