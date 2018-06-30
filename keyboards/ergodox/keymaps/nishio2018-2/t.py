data = """
"""


data = """
1 ? ?
2 ? ?
3 ? ?
4 ? ?
5 ? ?
6 ? ?
7 ? ?
8 ? ?
9 ? ?
0 ? ?
? xa ?
ka e ga
ta ri da
ko xya go
sa re za
ra pa yo
ti di ni
ku gu ru
tu du ma
? pi xe

u wo vu
si a ji
te na de
ke xyu ge
se mo ze
ha ba mi
to do o
ki gi no
i po xyo
nn ? xtu

? xu ?
hi - bi
su ro zu
fu ya bu
he xi be
me pu nu
so zo yu
ne pe mu
ho bo wa
? ? xo
"""

special_id = 0
def format(seq):
    global special_id
    if seq[0] == "?":
        special_id += 1
        return "KC_NO, {}".format(special_id)
    if seq == "-":
        return "KC_MINUS"
    return ", ".join("KC_{}".format(c) for c in seq.upper())

i = 0
for line in data.strip().split("\n"):
    if not line: continue
    base, lshift, rshift = line.split()
    comment = ("M(%d):" % i).ljust(7) +  "%s" % line.ljust(12)
    print("/*%s*/ {.base={%s}, .lshift={%s}, .rshift={%s}}," % (
        comment, format(base), format(lshift), format(rshift)
    ))
    i += 1
