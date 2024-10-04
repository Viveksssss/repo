from manim import *
from colour import Color
# config.background_color = BLACK
# config.frame_height = 10
# config.frame_width = 10

# config.pixel_height = 500
# config.pixel_width = 500
class Try(Scene):    
    def construct(self):
        ax = Axes(x_range=(-3,3),y_range=(-3,3))
        curve = ax.plot(lambda x: (x+2)*x*(x-2)/2, color=RED)
        area = ax.get_area(curve, x_range=(-2,2), color=BLUE)
        self.play(Create(ax, run_time=2))
        self.play(Create(curve, run_time=2))
        self.play(FadeIn(area, run_time=2))
        self.wait(2)

class SquareToCircle(Scene):
    def construct(self):
        square = Square(color=BLUE,fill_opacity=0.5)
        self.play(DrawBorderThenFill(square))
        circle =Circle(color=RED, fill_opacity=0.5)
        self.play(Transform(square, circle))
        self.play(Indicate(square, color=RED))
        self.wait(2)
        # self.play(FadeOut(circle))#althought square is transformed to circle,the mobject in screen still remains as square,so we need to fadeout the square to remove it from screen.
        # or use ReplacementTransform(square, circle) to replace square with circle,then we don't need to fadeout square.Instead,we can fadeout circle.
        self.play(FadeOut(square))

class Position(Scene):
    def construct(self):
        plane = NumberPlane()
        self.add(plane)
        dot = Dot(color = RED)
        green_dot = Dot(color = GREEN)
        green_dot.next_to(dot, RIGHT+UP, buff=0.5)
        self.add(dot, green_dot)
        s = Square(color=BLUE, fill_opacity=0.5)
        # shift
        s.shift(UP*2,LEFT*2)
        self.add(s)
        # move_to
        c = Circle(color=RED, fill_opacity=0.5)
        c.move_to([3,2,3])
        self.add(c)
        # align_to
        c2 = Circle(radius = 0.5,color=GREEN, fill_opacity=0.5)
        # self.add(Cross(scale_factor=0.2).move_to(c.get_critical_point(d)))

        c3 = c2.copy().set_color(YELLOW)
        c4 = c2.copy().set_color(PINK)
        c2.align_to(s,UP)
        c3.align_to(s,LEFT+UP)
        c4.align_to(s,RIGHT)
        self.add(c2,c3,c4)


class CriticalPoints(Scene):
    def construct(self):
        c= Circle(color=BLUE, fill_opacity=0.5)
        self.add(c)
        for d in [(0,0,0),UP,UR,RIGHT,DR,DOWN,DL,LEFT,UL]:
            s=Square(color=RED, fill_opacity=0.5)
        s.move_to([-3,1,0],aligned_edge=LEFT)
        self.add(s)

from manim.utils.unit import Percent,Pixels

class UsefulUnits(Scene):
    def construct(self):
        for per in range(5,51,5):
            self.add(Circle(radius=per*Percent(X_AXIS),color=BLUE))
            self.add(Square(side_length=per*Percent(X_AXIS),color=RED))

        d = Dot()
        d.shift( 100* Pixels*RIGHT)
        self.add(d)
class Grouping(Scene):
    def construct(self):
        reddot = Dot(color=RED)
        greendot = Dot(color=GREEN)
        bluedot = Dot(color=BLUE)
        # group = VGroup(*[reddot, greendot, bluedot]) # this is the same as below
        # VGroup do not accept iterator or list as arguments,so we need to use * to unpack the list or iterator oterwise it will be treated as a single argument.
        group = VGroup(reddot, greendot, bluedot)
        group.to_edge(RIGHT)
        self.add(group)

        circles = VGroup(*[Circle(radius = 0.05) for i in range(10)])
        # if we add circles directly to scene,it will be added as a single mobject
        # so we need to group them fitst and then arrange them before adding to scene.
        circles.arrange(RIGHT, buff=0.1)
        self.add(circles)

        stars = VGroup(*[Star(color = YELLOW, fill_opacity=0.5).scale(0.2) for i in range(20)])
        stars.arrange_in_grid(4,5,buff = 0.2)
        self.add(stars)


class SimpleScene(Scene):
    def construct(self):
        t = Triangle(color=BLUE, fill_opacity=0.5).align_to([0,0,0],DOWN)
        plane = NumberPlane(x_range=[-3,3], y_range=[-3,3])
        self.add(t,plane)

class ChangeDefaults(Scene):
    def construct(self):
        Text.set_default(font="Arial", color=WHITE,font_size=24)
        t = Text("Hello World", font_size=100,color = BLUE)
        t2 = Text("Goodbye!").next_to(t,DOWN)
        self.play(FadeIn(t))
        self.wait(1)
        self.play(FadeIn(t2))
        self.wait(1)
        self.play(FadeOut(t,t2))

class BasicAnimations(Scene):
    def construct(self):
        ploys = VGroup(
            *[RegularPolygon(5,radius = 1,color = RED,fill_opacity=0.5) for i in range(5)]
        ).arrange(RIGHT)

        self.play(DrawBorderThenFill(ploys),run_time=2)
        t = Text("Hello World", font_size=24,color = BLUE).to_edge(DOWN)
        self.wait(1)
        self.play(
            Write(t),
            Rotate(ploys[0],PI*20,rate_func = lambda t : t),
            Rotate(ploys[1],PI*20,rate_func = lambda t : smooth(t)),
            Rotate(ploys[2],PI*20,rate_func = there_and_back),
            Rotate(ploys[3],PI*20,rate_func = lambda t :np.sin(t*PI)),
            Rotate(ploys[4],PI*20,rate_func = lambda t :np.cos(t*PI/2)),
            run_time = 3,
        )
        self.play(Rotate(Square(color = GREEN),-PI),run_time=2)

class LaggingGroup(Scene):
    def construct(self):
        squares = VGroup(*[Square(color = Color(hue = i/20)) 
        for i in range(20)]).arrange_in_grid(4,5).scale(0.5)
        
        self.play(AnimationGroup(*[FadeIn(s) for s in squares],lag_ratio=0.1),run_time=2)
        self.wait(1)
        # t = Group(*[Text(f"{i/20}",font_size=10) for i in range(20)]).arrange(RIGHT,buff=0.1)
        # self.play(AnimationGroup(*[Write(t[i]) for i in range(20)],lag_ratio=0.1),run_time=6)