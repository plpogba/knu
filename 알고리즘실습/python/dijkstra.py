INF = 0xffff

def print_table(n, table):
    if n < 2:
        print()
        return
    print(' '.join(str(table[i]) for i in range(2, n+1)))

def print_path(table, n):
    if n == 1:
        print(1)
        return
    path = []
    i = n
    while table[i] != 1:
        path.append(i)
        i = table[i]
    path.append(i)
    
    result = [1] + path[::-1]
    print(' '.join(map(str, result)))

def dijkstra(n, W):
    touch = [0] * (n + 1)
    length = [0] * (n + 1)
    F = []

    if n == 1:
        print_table(n, touch)
        return touch, F

    for i in range(2, n + 1):
        touch[i] = 1
        length[i] = W[1][i]
    print_table(n, touch)

    for _ in range(n - 1):
        min_val = INF
        vnear = -1
        for i in range(2, n + 1):
            if 0 <= length[i] < min_val:
                min_val = length[i]
                vnear = i
        if vnear == -1:
            break

        F.append((touch[vnear], vnear, min_val))

        for i in range(2, n + 1):
            if length[vnear] + W[vnear][i] < length[i]:
                length[i] = length[vnear] + W[vnear][i]
                touch[i] = vnear
        length[vnear] = -1
        print_table(n, touch)

    return touch, F

def main():
    n, k = map(int, input().split())

    W = [[INF] * (n + 1) for _ in range(n + 1)]
    for i in range(n + 1):
        W[i][i] = 0

    for _ in range(k):
        u, v, w = map(int, input().split())
        W[u][v] = w

    c = int(input())
    testcases = [int(input()) for _ in range(c)]

    touch, F = dijkstra(n, W)

    for u, v, w in F:
        print(u, v, w)

    for t in testcases:
        print_path(touch, t)

if __name__ == "__main__":
    main()