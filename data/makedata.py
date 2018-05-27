def ptr2str(p):
    return '%d %d %d' % (p[0], p[1], p[2])

def face2str(a, b, c, d, col, smooth=0):
    return '\n'.join(['triangle %s %s %s %s %f' %
                      (ptr2str(a), ptr2str(b), ptr2str(c),
                          ptr2str(col), smooth),
                      'triangle %s %s %s %s %f' %
                      (ptr2str(d), ptr2str(b), ptr2str(c),
                          ptr2str(col), smooth)])

def ball(c, r, col, smooth=1, alpha=0, n=1):
    return 'ball %s %f %s %f %f %f' % (ptr2str(c), r, ptr2str(col), smooth,
                                       alpha, n)

with open('data/faces.mypoints', 'w') as f:
    sz = [ 100, 200, 100 ]
    facestrs = []
    for axe in range(0):
        pa = []
        pb = []
        for i in range(2):
            for j in range(2):
                if axe == 0:
                    p = [0, i * sz[1], j * sz[2]]
                elif axe == 1:
                    p = [i * sz[0], 0, j * sz[2]]
                else:
                    p = [i * sz[0], j * sz[1], 0]
                pa.append(p)
                q = [ sz[x] if x == axe else p[x] for x in range(3) ]
                pb.append(q)
        if axe == 0: 
            (r, g, b) = (200, 100, 100)
        elif axe == 1: 
            (r, g, b) = (256, 256, 256)
        else:
            (r, g, b) = (100, 100, 100)
        facestrs.append(face2str(pa[0], pa[1], pa[2], pa[3], r, g, b))
        if axe == 0: 
            (r, g, b) = (100, 100, 200)
        elif axe == 1: 
            (r, g, b) = (100, 200, 100)
        else:
            (r, g, b) = (200, 200, 100)
        facestrs.append(face2str(pb[0], pb[1], pb[2], pb[3], r, g, b))
    facestrs.append(face2str((-100, 0, 0), (300, 0, 0),
                             (-100, 300, 0), (100, 300, 0),
                             (60, ) * 3, smooth=0.01))
    facestrs.append(face2str((0, 0, 0), (200, 0, 0),
                             (0, 0, 200), (200, 0, 200),
                             (512, ) * 3))
    facestrs.append(face2str((10, 50, 100), (70, 50, 100),
                             (10, 100, 100), (70, 100, 100),
                             (512, ) * 3))
    facestrs.append(ball((20, 20, 10), 10, (255, 255, 255), 0.9, 0.9, 1.3))
    facestrs.append(ball((70, 80, 40), 20, (255, 255, 0), 0, 0, 1))
    f.write('\n'.join(facestrs))

