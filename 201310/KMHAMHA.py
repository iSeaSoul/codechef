def dfs(id, graph, vis, match):
    for vertex in graph[id]:
        if vis[vertex]:
            continue
        vis[vertex] = True
        if match[vertex] == -1 or dfs(match[vertex], graph, vis, match):
            match[vertex] = id
            return True
    return False

def hungray(graph, n, m):
    match = [-1 for i in xrange(m)]
    match_cnt = 0
    for idx in xrange(n):
        vis = [False for i in xrange(m)]
        if dfs(idx, graph, vis, match):
            match_cnt += 1
    return match_cnt

def get_id(id_map, id_map_cnt, axis):
    if not id_map.has_key(axis):
        id_map[axis] = id_map_cnt
        id_map_cnt += 1
    return id_map[axis], id_map_cnt

case_num = input()
for case in xrange(case_num):
    map_x = {}
    map_y = {}
    map_x_cnt = 0
    map_y_cnt = 0
    
    graph = []
    
    for pair_id in xrange(input()):
        x, y = map(int, raw_input().split())
        idx, map_x_cnt = get_id(map_x, map_x_cnt, x)
        idy, map_y_cnt = get_id(map_y, map_y_cnt, y)
        if idx >= len(graph): graph.append([])
        graph[idx].append(idy)
    
    print hungray(graph, map_x_cnt, map_y_cnt)
