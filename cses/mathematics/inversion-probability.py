n = int(input())
a = list(map(int, input().split()))
 
ans = 0
den = 1
for x in a:
    den *= x
for i in range(len(a)):
    for j in range(i + 1, len(a)):
        cur = 0
        for x in range(2, a[i] + 1):
            cur += min(x - 1, a[j])
        ans += cur * (den // (a[i] * a[j]))
 
print(f"{ans/den:.6f}")
