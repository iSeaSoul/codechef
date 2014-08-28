def cal_area(axis):
    px1, py1 = axis[2] - axis[0], axis[3] - axis[1]
    px2, py2 = axis[4] - axis[0], axis[5] - axis[1]
    return abs(px1 * py2 - py1 * px2)

n = input()
max_area = min_area = cal_area(map(int, raw_input().split()))
max_id = min_id = 1

for xid in xrange(1, n):
    area = cal_area(map(int, raw_input().split()))
    if area <= min_area:
        min_area, min_id = area, xid + 1
    if area >= max_area:
        max_area, max_id = area, xid + 1

print min_id, max_id
