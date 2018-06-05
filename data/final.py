from utils import *

def makescene():
    sz = [ 100, 200, 100 ]
    facestrs = []
    # Floor
    facestrs.append(face2str((-300, 0, 0), (300, 0, 0),
                             (-300, 300, 0), (300, 300, 0),
                             (90, ) * 3, smooth=0.00001))
    # Top light
    facestrs.append(face2str((-20, 0, 100), (-20, 200, 100),
                             (120, 0, 120), (0, 200, 120),
                             (512, ) * 3))
    facestrs.append(face2str((150, 0, 140), (150, 200, 140),
                             (180, 0, 120), (180, 200, 120),
                             (512, ) * 3))
    curves = [
        [(0, 0), (0, 10), (3, 3)],
        [(3, 3), (6, 2), (9, 4)],
        [(9, 4), (10, 6), (11, 4)],
        [(11, 4), (15, 8), (20, 0)]
    ]
    z = 0
    for curve in curves:
        print_curve(curve)
        dz = curve[2][0] - z
        facestrs.append(bezierCurve((10, 90, z * 4), (0, 0, dz * 4),
                                    curve,
                                    (55, ) * 3, smooth=0.5))
        z += dz
    facestrs.append(ball((10, 90, z + 10), 10, (55, ) * 3, smooth=0.5))
    return facestrs
    # Back light
    back_light = False
    if back_light:
        facestrs.append(face2str((0, 0, 0), (100, 0, 0),
                                (0, 0, 100), (100, 0, 100),
                                (256, ) * 3))
    # Red Mirror
    facestrs.append(face2str((0, 200, 0), (150, 40, 0),
                             (0, 200, 100), (150, 40, 100),
                             (255, 200, 200), smooth = 1))
    # Solid ball
    facestrs.append(ball((50, 100, 20), 15, (225, 225, 225), smooth=0, 
                    alpha=0, n=1))
    # Ball shadow
    facestrs.append(face2str((35, 85, 2), (65, 85, 2),
                             (35, 115, 2), (65, 115, 2),
                             (99, 0, 0), smooth = 0))
    # Left wall
    facestrs.append(face2str((0, 0, 0), (0, 200, 0),
                             (0, 0, 100), (0, 200, 100),
                             (255, 255, 200), smooth = 0))
    return facestrs


with open('data/faces_f.mypoints', 'w') as f:
    facestrs = makescene()
    f.write('\n'.join(facestrs))

def makecam(wid=2., hei=1.6):
    eye = (50., 3., 50.)
    vb = (50. - wid / 2, 3.9, 50. - hei / 2)
    vx = (wid, 0, 0)
    vy = (0, 0, hei)
    return [ptr2str(i) for i in [eye, vb, vx, vy]]

with open('data/cam.mypoints', 'w') as f:
    camstrs = makecam()
    f.write('\n'.join(camstrs))
