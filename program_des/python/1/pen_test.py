import turtle

turtle.colormode(255)
screen = turtle.Screen()
pen = turtle.Turtle()

step = 6
times = 360
pen.speed(0)
pen.hideturtle()

# color def
c1 = (31, 111, 201)
c2 = (24, 177, 162)
c3 = (182, 31, 162)
c4 = (31, 111, 201)
colors = [c1, c2, c3, c4]

turtle.delay(0)
screen.tracer(0, 0)

# color insert
def lerp_color(c_start, c_end, t, total):
    r = c_start[0] + (c_end[0] - c_start[0]) * t / total
    g = c_start[1] + (c_end[1] - c_start[1]) * t / total
    b = c_start[2] + (c_end[2] - c_start[2]) * t / total
    return (int(r), int(g), int(b))

# init
pen.penup()
pen.goto(0, 0)
pen.pendown()

# multi_color
segments = len(colors) - 1
steps_per_segment = times // segments

for seg in range(segments):
    start = colors[seg]
    end = colors[seg + 1]
    for i in range(steps_per_segment):
        pen.pencolor(lerp_color(start, end, i, steps_per_segment))
        for j in range(times):
            pen.forward(step)
            pen.right(360 / times)
        pen.right(360 / times)

screen.update()
turtle.done()

