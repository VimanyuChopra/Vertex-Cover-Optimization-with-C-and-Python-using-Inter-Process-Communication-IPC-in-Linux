#!/usr/bin/env python
# coding: utf-8

# In[ ]:


#!/usr/bin/env python
# coding: utf-8

# In[3]:


import re
import sys


# YOUR CODE GOES HERE
class Vertex(object):

    def __init__(self, x, y):
        self.x = float(x)
        self.y = float(y)

        self.point = '(' + str(x) + ',' + str(y) + ')'
        self.point_list = []

    def __repr__(self):
        return '({0:.2f},{1:.2f})'.format(self.x, self.y)


class Line(object):
    def __init__(self, p1, p2):
        self.src = p1
        self.dst = p2

    def __repr__(self):
        return repr(self.src) + "to" + repr(self.dst)


def collinear(q, j, i):
    """
    if (q.x - i.x) * (j.y - i.y) == (j.x - i.x) * (q.y - i.y) and min(i.x, j.x) <= q.x <= max(i.x, j.x) and min(i.y,
                                                                                                                j.y) <= q.y <= max(
        i.y, j.y):
        return 1
    else:
        pass

    if (q.[0] - i.[0]) * (j.[1] - i.[1]) == (j.[0] - i.[0]) * (q.[1] - i.[1]) and min(i.[0], j.[0]) <= q.[0] <= max(i.[0], j.[0]) and min(i.[1],
                                                                                                                j.[1]) <= q.[1] <= max(
        i.[1], j.[1]):

    if ((q[0] - i[0]) * (j[1] - i[1]) == (j[0] - i[0]) * (q[1] - i[1])) and (min(i[0], j[0]) <= q[0] <= max(i[0], j[0])) and (min(i[1],j[1]) <= q[1] <= max(i[1], j[1])):

        return 1
    else:
        return 0

    if (q[0]*(j[1]-i[1])+j[0]*(i[1]-q[1])+i[0]*(j[1]-q[1])):
    """
    if (q[0] - j[0]) * (j[1] - i[1]) != (j[0] - i[0]) * (q[1] - j[1]):

        return 0
    else:
        return 1


def intersect(A, B, C, D):
    a = B[1] - A[1]
    b = A[0] - B[0]
    c = a * (A[0]) + b * (A[1])
    c = -c

    d = D[1] - C[1]
    e = C[0] - D[0]
    f = d * (C[0]) + e * (C[1])
    f = -f
    den = (a * e - d * b)
    if den == 0:
        # print("no intersection found")
        return None
    else:
        x = (b * f - e * c) / den
        y = (d * c - a * f) / den
        if min(A[0], B[0]) <= x <= max(A[0], B[0]) and min(A[1], B[1]) <= y <= max(A[1], B[1]):
            if min(C[0], D[0]) <= x <= max(C[0], D[0]) and min(C[1], D[1]) <= y <= max(C[1], D[1]):
                return x, y
        return None


# intersection_point = intersect(A, B, C, D)


# print(intersection_point)

def generate(street_db):
    vertices_list = []
    tempendpoint_list = []
    endpoint_list = []
    final_vertices_list = []
    intersection_list_only = []
    intersection_dict = {}
    final_intersection_list = []
    list_for_edges = []
    vertices = {}
    traverse = []
    edge_list = []

    street_n = list(street_db.keys())

    for a in range(len(street_db) - 1):

        for b in range(a + 1, len(street_db)):

            street1_coords = street_db[street_n[a]]
            street2_coords = street_db[street_n[b]]

            for i in range(len(street1_coords) - 1):

                for j in range(len(street2_coords) - 1):
                    intersection = intersect(street1_coords[i], street1_coords[i + 1], street2_coords[j],
                                             street2_coords[j + 1])

                    # list_for_edges.append([intersection, street1_coords[i], street1_coords[i + 1], street2_coords[j], street2_coords[j + 1]])
                    if intersection is not None:
                        intersection_dict.setdefault(intersection, []).append(street2_coords[j])

                        intersection_dict.setdefault(intersection, []).append(
                            street2_coords[j + 1])

                        intersection_dict.setdefault(intersection, []).append(street1_coords[i])
                        intersection_dict.setdefault(intersection, []).append(street1_coords[i + 1])

                        # intersection_dict[intersection]=[street1_coords[i], street1_coords[i + 1], street2_coords[j],
                        #                    street2_coords[j + 1]]
                        tempendpoint_list.append(intersection)
                        tempendpoint_list.append(street1_coords[i])
                        tempendpoint_list.append(street1_coords[i + 1])
                        tempendpoint_list.append(street2_coords[j])
                        tempendpoint_list.append(street2_coords[j + 1])

    for i in intersection_dict:
        v = intersection_dict[i]

        finint = []
        for k in v:

            if k not in finint:
                finint.append(k)
        intersection_dict[i] = finint

    for k in intersection_dict:
        final_intersection_list.append(k)

    for i in tempendpoint_list:
        if i in endpoint_list:
            continue
        else:
            endpoint_list.append(i)

    for index, value in enumerate(endpoint_list):
        index = index + 1
        # vertices[index]=value
        vertices[index] = value
      
     # print no. of vertices for a3
    sys.stdout.write('V {}\n'.format(len(vertices)))
    # print(len(vertices_list))
    sys.stdout.flush()
    
        


    collist = []
    fincollist = []
    clist = []
    nclist = []
    final_edge_list = []
    flist = []
    final_edges = []

    for i in intersection_dict:
        for j in intersection_dict[i]:
            clist.append((i, j))

        if len(final_intersection_list) > 1:
            for k in clist:
                yo = k[0]
                end = k[1]
                for j in range(len(final_intersection_list)-1):
                    v1 = final_intersection_list[j]
                    v2 = final_intersection_list[j + 1]

                    x = collinear(v1, v2, end)

                    if x == 1:

                        collist.append([v1, v2, end])
                    else:
                        edge_list.append((yo, end))
        else:
            for i in intersection_dict:
                for j in intersection_dict[i]:
                    edge_list.append((i, j))
                #
                # k=intersection_dict(i)
                # for y in k:
                # edge_list.append((i,y))
    try:

        for i in collist:

            if i in fincollist:
                continue
            else:
                fincollist.append(i)

        for k in fincollist:
            slist = []

            if k[0][0] == k[1][0] == k[2][0]:
                slist.append(k[0][1])
                slist.append(k[1][1])
                slist.append(k[2][1])
                slist.sort()

                nclist.append(((k[0][0], slist[0]), (k[0][0], slist[1])))
                nclist.append(((k[0][0], slist[1]), (k[0][0], slist[2])))

                edge_list.append(((k[0][0], slist[0]), (k[0][0], slist[1])))
                edge_list.append(((k[0][0], slist[1]), (k[0][0], slist[2])))


    except:
        pass

    for i in edge_list:
        if i in final_edge_list:
            continue
        else:
            final_edge_list.append(i)

    global velist
    for i in final_edge_list:
        velist = []

        for j in i:
            for key, value in vertices.items():
                if value == j:
                    velist.append(key)
                    flist.append(velist)

    for i in flist:
        if i in final_edges:
            continue
        else:
            final_edges.append(i)
         
    # print(final_edges) for a3
    for i in final_edges:
    	
        if i[0]==i[1]:
            final_edges.remove(i)
        
    
    sys.stdout.write("E {")
    sys.stdout.flush()
    for h in range(0,len(final_edges)):
        if h!=(len(final_edges)-1):
            
            #print("<" + str(final_edges[h][0]) + "," + str(final_edges[h][1]) + ">,")
            sys.stdout.write(str('<') + str(final_edges[h][0]) + str(',') + str(final_edges[h][1]) + str('>') + str(','))
            sys.stdout.flush()
        else:
            #print("<" + str(final_edges[h][0]) + "," + str(final_edges[h][1]) + ">" + "}")
            sys.stdout.write(str('<') + str(final_edges[h][0]) + str(',') + str(final_edges[h][1]) + str('>'))
            sys.stdout.flush()
            
            
    sys.stdout.write('}\n')
    sys.stdout.flush()

"""

def inp_values(command):
    try:
        # name = re.findall(name_rx, command)[0]
        cmd = command.split('"')
        # print(cmd[1])
        if len(cmd) >= 1:
        
        street_name = cmd[1]
        name = street_name
        
        return name
    except:
        IndexError
"""
def inp_values(command):
    try:
        cmd = command.split('"')
        # print(cmd[1])
        if len(cmd) >= 1:

            street_name = cmd[1]

            
        else:
            return

        return street_name

    except:
        IndexError



def add_street(command, name, coord_rx):
    #street_dict[name] = coord_rx

    # pattern = r'add \"(.+?)\"(( ?\(\-?\d+,\-?\d+\))+)\s*$'
    #pattern = r'^add\s*\"(.*)\"\s*(\(.*\))$'
    pattern = r'add \"(.+?)\"(( ?\(\-?\d+,\-?\d+\))+)\s*$'

    if re.match(pattern, command):
        street_dict[name] = coord_rx

        street_name = name

        point_list = inp_line(command)



    else:
        print('Error: The format of input is wrong.')


def inp_line(points):
    try:
        line_list = []
        # print(point_list)

        for i in range(len(inp_point(points)) - 1):
            l = Line(inp_point(points)[i], inp_point(points)[i + 1])

            line_list.append(l)

        return line_list

    except:
        TypeError

    # print(line_list)


def inp_point(command):
    point_list = []
    line_list = []
    try:

        cmd = command.split('"')

        vertex_list = cmd[2]

        pattern = re.compile(r'\((\-?\d+),(\-?\d+)\)')

        points = pattern.findall(vertex_list)

        for p in points:
            vert = Vertex(p[0], p[1])

            if vert not in point_list:
                point_list.append(vert)

        if len(point_list) < 2:
            print('Error: Not enough points')

        return point_list


    except:
        print("error")


def modify_street(command, name, coord_rx):
    pattern = r'mod \"(.+?)\"(( ?\(\-?\d+,\-?\d+\))+)\s*$'

    if re.match(pattern, command):

        cmd = command.split('"')
        street_name = cmd[1]

        vertex_list = cmd[2]

        street_dict[name] = coord_rx

    else:
        print('Error: The input fomrat is incorrect')


def main():
    ### YOUR MAIN CODE GOES HERE

    ### sample code to read from stdin.

    ### make sure to remove all spurious print statements as required

    ### by the assignment
    

    global street_dict
    street_dict = {}

    while True:
        try:
            if len(sys.argv) > 1:
                command = sys.stdin.readline()
            else:
                command = input('').lower()

            command = command.lower()
            name = inp_values(command)

            num_rx = '-?\d+'
            coord_rx = r'\(\s*' + num_rx + '\s*,\s*' + num_rx + '\s*\)'
            coord_rx = re.findall(coord_rx, command)
            coord_rx = [eval(i) for i in coord_rx]
            if command == '':
                break

            elif command[0:3] == 'add':

                if name in street_dict:
                    print('Error: this street is already exist.')
                else:
                    add_street(command, name, coord_rx)
                    # print(key)


            elif command[0:3] == 'mod':

                if name in street_dict:
                    modify_street(command, name, coord_rx)

                else:
                    print('Error: this street does not exsit, try again')

            elif command[0:2] == 'rm':
                # print('remove')
                if name in street_dict:
                    del street_dict[name]

                else:
                    print('Error: this street does not exsit, try again')

            elif command[0:2] == 'gg':

                generate(street_dict)

            else:

                print('Error: The format of input is wrong.')


        except EOFError:
            sys.exit(0)
            # print('Finished reading input')


if __name__ == '__main__':
    main()

# In[ ]:

