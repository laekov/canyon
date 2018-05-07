def ptr2str(p):
    return '%d %d %d' % (p[0], p[1], p[2])

def face2str(a, b, c, d, r, g, bl):
    smooth = .0001
    return '\n'.join([ '%s %s %s %d %d %d %f' % ( ptr2str(a), ptr2str(b), ptr2str(c), r, g, bl, smooth),
        '%s %s %s %d %d %d %f' % ( ptr2str(d), ptr2str(b), ptr2str(c), r, g, bl, smooth) ])

with open('data/faces.mypoints', 'w') as f:
    sz = [ 100, 200, 100 ]
    facestrs = []
    for axe in range(3):
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
    if True:
        facestrs.append(face2str(
            (10, 20, 98), (10, 80, 98), (48, 20, 98), (48, 80, 98), 256, 256, 256))
        facestrs.append(face2str(
            (52, 120, 98), (52, 180, 98), (90, 120, 98), (90, 180, 98), 256, 256, 256))
        #facestrs.append(face2str(
            #(10, 120, 98), (20, 130, 88), (10, 130, 98), (20, 120, 88), 30, 1, 1))
    f.write('\n'.join(facestrs))

