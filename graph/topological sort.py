def top(node):
    vis[node] = True
    for n in graph[node]:
        if not vis[n]:
            top(n)
    order.append(node)
    
