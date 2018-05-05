def ptr2str(p):
    return '%d %d %d' % (p[0], p[1], p[2])

def face2str(a, b, c, d, r, g, bl):
    return '\n'.join([ '%s %s %s %d %d %d' % ( ptr2str(a), ptr2str(b), ptr2str(c), r, g, bl),
        '%s %s %s %d %d %d' % ( ptr2str(d), ptr2str(b), ptr2str(c), r, g, bl) ])

with open('data/faces.mypoints', 'w') as f:
    sz = 100
    facestrs = []
    for axe in range(3):
        pa = []
        pb = []
        for i in range(2):
            for j in range(2):
                if axe == 0:
                    p = [0, i * sz, j * sz]
                elif axe == 1:
                    p = [i * sz, 0, j * sz]
                else:
                    p = [i * sz, j * sz, 0]
                pa.append(p)
                p[axe] = sz
                pb.append(p)
        if axe == 0: 
            (r, g, b) = (255, 0, 0)
        elif axe == 1: 
            (r, g, b) = (0, 255, 0)
        else:
            (r, g, b) = (55, 55, 55)
        facestrs.append(face2str(pa[0], pa[1], pa[2], pa[3], r, g, b))
        if axe == 0: 
            (r, g, b) = (0, 0, 0)
        elif axe == 1: 
            (r, g, b) = (0, 0, 255)
        else:
            (r, g, b) = (55, 55, 55)
        facestrs.append(face2str(pb[0], pb[1], pb[2], pb[3], r, g, b))
        f.write('\n'.join(facestrs))

