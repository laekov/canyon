def ptr2str(p):
    return ' '.join([str(c) for c in p])

def face2str(a, b, c, d, col, smooth=0):
    return '\n'.join(['Triangle %s %s %s %s %f' %
                      (ptr2str(a), ptr2str(b), ptr2str(c),
                          ptr2str(col), smooth),
                      'Triangle %s %s %s %s %f' %
                      (ptr2str(d), ptr2str(b), ptr2str(c),
                          ptr2str(col), smooth)])

def ball(c, r, col, smooth=1, alpha=0, n=1):
    return 'Ball %s %f %s %f %f %f' % (ptr2str(c), r, ptr2str(col), smooth,
                                       alpha, n)

def bezierCurve(a, v, pts, col, smooth=1, alpha=0, n=1):
    pts_str = ' '.join([ptr2str(p) for p in pts])
    return 'CurveRot %s %s %s %f %f %f %d %s' % (ptr2str(a), ptr2str(v),
                                              ptr2str(col), smooth, alpha, n,
                                              len(pts), pts_str)

def print_curve(pts):
    n = len(pts)
    x = [0] * n
    y = [0] * n
    x[0] = [str(p[0]) for p in pts]
    y[0] = [str(p[1]) for p in pts]
    for p in pts:
        print('{x: %f + sin(t) * 0.2, y: %f + cos(t) * 0.2, min: 0, max: 6.28};' %
              (p[0], p[1]))
    for i in range(1, n):
        x[i] = ['(%s)*t + (%s)*(1-t)' % (x[i - 1][j], x[i - 1][j + 1]) for j in range(n - i)]
        y[i] = ['(%s)*t + (%s)*(1-t)' % (y[i - 1][j], y[i - 1][j + 1]) for j in range(n - i)]
    print('{')
    print('x: %s,' % x[n - 1][0])
    print('y: %s,' % y[n - 1][0])
    print('min: 0, max: 1}')
    
