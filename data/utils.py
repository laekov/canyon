def ptr2str(p):
    return '%f %f %f' % (p[0], p[1], p[2])

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

