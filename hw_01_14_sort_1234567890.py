names = [

    "차지훈",

    "김민준", "이도현", "박서준", "정현우", "최지호",

    "장우진", "윤태현", "조민성", "오준호", "한시우",

    "김서연", "이지민", "박하윤", "정다은", "최예린",

    "장수아", "윤지아", "조하늘", "오소율", "한은채",

    "서지후", "배도윤", "임하람", "강유진", "노은서",

    "문채린", "신예준", "류아린", "홍지호", "곽서현"

]

def sort_insert(arr, start, end_inclusive):
    for i in range(start + 1, end_inclusive + 1):
        v = arr[i]
        j = i - 1
        while j >= start and arr[j] > v:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = v

def merge(arr, start, mid, end_inclusive):
    merged = []
    l, r = start, mid
    while l < mid and r <= end_inclusive:
        if arr[l] <= arr[r]:
            merged.append(arr[l])
            l += 1
        else:
            merged.append(arr[r])
            r += 1

    while l < mid:
        merged.append(arr[l])
        l += 1
    while r <= end_inclusive:
        merged.append(arr[r])
        r += 1

    l = start
    for n in merged:
        arr[l] = n
        l += 1

def sort_merge(arr, start, end_inclusive):
    if end_inclusive <= start: return
    if end_inclusive < start + 5:
        sort_insert(arr, start, end_inclusive)
        return
    mid = (start + end_inclusive) // 2
    sort_merge(arr, start, mid)
    sort_merge(arr, mid + 1, end_inclusive)
    merge(arr, start, mid + 1, end_inclusive)


def sort_quick(arr, start, end_inclusive):
    pass


def main():
    last = len(names) - 1

    arr = names[:]

    print('=' * 60)

    print(f'ME< {arr}')

    sort_merge(arr, 0, last)

    print(f'ME> {arr}')

    arr = names[:]

    print('=' * 60)

    print(f'QU< {arr}')

    sort_quick(arr, 0, last)

    print(f'QU> {arr}')

    print(f'My name index = {arr.index(names[0])}')

if __name__ == '__main__':
  main()