directions = [(0, -1), (1, 0), (0, 1), (-1, 0)]
data = []
width = 0
height = 0
guard_path = set()
start_x = 0
start_y = 0

def presolve(input_data):
    global data, width, height, start_x, start_y, guard_path
    data = input_data.strip().split("\n")
    width = len(data[0])
    height = len(data)
    # Locate the starting position of the guard
    for j in range(height):
        for i in range(width):
            if data[j][i] == '^':
                start_x, start_y = i, j
                break
    guard_path = walk(None)[0]

def is_within_bounds(x, y):
    return x in range(width) and y in range(height)

def walk(obstacle):
    obstacle_x, obstacle_y = obstacle if obstacle else (-1, -1)
    direction = 0
    x, y = start_x, start_y
    loop = False
    positions = set()
    while is_within_bounds(x, y):
        if (x, y, direction) in positions:
            loop = True
            break
        positions.add((x, y, direction))
        nx, ny = x + directions[direction][0], y + directions[direction][1]
        while is_within_bounds(nx, ny) and (data[ny][nx] == '#' or (nx == obstacle_x and ny == obstacle_y)):
            direction = (direction + 1) % 4
            nx, ny = x + directions[direction][0], y + directions[direction][1]
        x, y = nx, ny
    path = {(pos[0], pos[1]) for pos in positions}
    return path, loop

def solve_second() -> int:
    possible_positions = [
        pos for pos in guard_path if pos != (start_x, start_y)
    ]
    loop_positions = [pos for pos in possible_positions if walk(pos)[1]]
    return len(loop_positions)

input_data = ""

for line in open("data.txt"):
    input_data += line

presolve(input_data)

print(solve_second())