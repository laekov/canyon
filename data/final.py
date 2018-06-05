from utils import *

def makescene():
    sz = [ 100, 200, 100 ]
    facestrs = []
    # Floor
    facestrs.append(face2str((-300, 0, 0), (300, 0, 0),
                             (-300, 300, 0), (300, 300, 0),
                             (90, ) * 3, smooth=0.01))
    # Wall
    facestrs.append(face2str((-50, 0, 0), (-50, 300, 0),
                             (-50, 0, 100), (-50, 300, 100),
                             (255, 200, 200), smooth=0))
    facestrs.append(face2str((150, 0, 0), (150, 300, 0),
                             (150, 0, 100), (150, 300, 100),
                             (200, 255, 200), smooth=0))
    # Back
    facestrs.append(face2str((-50, 300, 0), (150, 300, 0),
                             (-50, 300, 100), (150, 300, 100),
                             (200, 200, 255), smooth=0))
    # Top light
    facestrs.append(face2str((-20, 50, 130), (-20, 150, 130),
                             (180, 50, 120), (180, 150, 120),
                             (512, ) * 3))
    curves = [
        [(0, 0), (0, 5), (3, 1.8)],
        [(3, 1.8), (6, 1.2), (7, 1.8)],
        [(7, 1.8), (8, 2.4), (9, 1.8)],
        [(9, 1.8), (10, 2.4), (12, 2.4)],
        [(12, 2.4), (12, 2.0), (11, 0)]
    ]

    l = 0.
    for curve in curves:
        print_curve(curve)
        dl = curve[2][0] - l
        x = l * 12 / 13 + 3
        z = l * 5 / 13 + 3
        dx = dl * 12 / 13
        dz = dl * 5 / 13
        facestrs.append(bezierCurve((x * 3, 90, z * 3), (dx * 3, 0, dz * 3),
                                    curve,
                                    (225, 225, 255), smooth=0.5, alpha=0.7))
        l += dl
   
    curves = [
        [(0, 0), (0, 7), (3, 1.8)],
        [(3, 1.8), (6, 1.2), (9, 1.8)],
        [(9, 1.8), (10, 2.4), (11, 1.8)],
        [(11, 1.8), (15, 3.6), (20, 0)]
    ]
    z = 0
    for curve in curves:
        # print_curve(curve)
        dz = curve[2][0] - z
        facestrs.append(bezierCurve((10, 120, z * 3), (0, 0, dz * 3),
                                    curve,
                                    (55, ) * 3, smooth=0.5))
        z += dz
    facestrs.append(ball((10, 120, z * 3 + 3), 3, (55, ) * 3, smooth=0.5))
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
