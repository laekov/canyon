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
def main():
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
            col = (200, 100, 100)
        elif axe == 1: 
            col = None
        else:
            col = (100, 100, 100)
        if col is not None:
            facestrs.append(face2str(pa[0], pa[1], pa[2], pa[3], col))
        if axe == 0: 
            col = (100, 100, 200)
        elif axe == 1: 
            col = (100, 200, 100)
        else:
            col = (200, 200, 100)
        if col is not None:
            facestrs.append(face2str(pb[0], pb[1], pb[2], pb[3], col))
    # Background
    facestrs.append(face2str((-50, 150, 0), (40, 120, 0),
                             (-50, 150, 100), (40, 120, 100),
                             (255, 255, 0), smooth=0))
    # Floor
    facestrs.append(face2str((-300, 0, 0), (300, 0, 0),
                             (-300, 300, 0), (300, 300, 0),
                             (90, ) * 3, smooth=0.00001))
    # Top light
    for i in range(0, 200, 20):
        facestrs.append(face2str((-20, i, 100), (-20, i + 10, 100),
                                 (0, i, 120), (0, i + 10, 120),
                                 (512, ) * 3))
        facestrs.append(face2str((120, i, 100), (120, i + 10, 100),
                                 (100, i, 120), (100, i + 10, 120),
                                 (512, ) * 3))
    # Back light
    back_light = False
    if back_light:
        facestrs.append(face2str((0, 0, 0), (100, 0, 0),
                                (0, 0, 100), (100, 0, 100),
                                (256, ) * 3))
    # Red Mirror
    facestrs.append(face2str((40, 200, 0), (200, 40, 0),
                             (40, 200, 100), (200, 40, 100),
                             (255, 200, 200), smooth = 0.9))
    # Glass ball
    facestrs.append(ball((40, 70, 22), 20, (255, 200, 200), smooth=0.999,
                    alpha=0.999, n=1.3))
    # Solid ball
    facestrs.append(ball((50, 100, 20), 15, (225, 120, 225), smooth=0, 
                    alpha=0, n=1))
    return facestrs


with open('data/faces.mypoints', 'w') as f:
    facestrs = main()
    f.write('\n'.join(facestrs))

