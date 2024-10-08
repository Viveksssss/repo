from manim import *
from colour import Color
import numpy as np
config.font_size = 24
# config.background_color = WHITE
# config.frame_height = 10
# config.frame_width = 10

# config.pixel_height = 500
# config.pixel_width = 500

# the command for rendering the animation is: manima -qk -p demo.py class_name
# of which after q,we can choose the quality of the animation
# k is for fourk, which means the resolution of the animation is 4k
# h is for hign quality, which means the resolution of the animation is 1080p
# m is for medium quality, which means the resolution of the animation is 720p
# l is for low quality, which means the resolution of the animation is 480p

# -p is for preview, which means the animation will be rendered in the preview window



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

from manim.scene.scene import Scene
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
        # squares = VGroup(*[Square(color =(int(i/20*255),int(i/20*255),int(i/20*255)),fill_opacity=0.5) 
        # for i in range(20)]).arrange_in_grid(4,5).scale(0.5)

        # self.play(AnimationGroup(*[FadeIn(s) for s in squares],lag_ratio=0.2),run_time=4)
        # self.wait(1)
        # t = Group(*[Text(f"{i/20}",font_size=10) for i in range(20)]).arrange(RIGHT,buff=0.1)
        # self.play(AnimationGroup(*[Write(t[i]) for i in range(20)],lag_ratio=0.1),run_time=6)

        square = Square(color = BLUE)

        self.play(square.animate) # just mobject can not be played,we can use animate method to create animation.
        self.play(square.animate.shift(UP*2))
        self.play(square.animate.scale(1/2).shift(LEFT*2))
        self.play(square.animate.shift(RIGHT*4))
        self.play(square.animate.shift(DOWN*2).rotate(PI/2))

class AnimateSyntax(Scene):
    def construct(self):
        s = Square(color=BLUE, fill_opacity=0.5)
        c = Circle(color=RED, fill_opacity=0.5)
        # self.add(s,c)
        self.play(s.animate.shift(UP),c.animate.shift(DOWN))
        self.play(VGroup(s,c).animate.arrange(RIGHT))
        self.play(c.animate(rate_func=linear).shift(RIGHT*2).scale(2))

class AnimateProblem(Scene):
    def construct(self):
        left_square = Square(color=BLUE, fill_opacity=0.5)
        right_square = Square(color=BLUE, fill_opacity=0.5)
        VGroup(left_square, right_square).arrange(RIGHT, buff=0.5)
        self.add(left_square, right_square)
        self.play(left_square.animate.rotate(PI),Rotate(right_square,PI/2),run_time=2)
        # the right_square is rotate correctly,but left_square is not,the animate mothed is not working correctly.
        self.wait(1)
        
class AnimateMechanisms(Scene):
    def construct(self):
        # c = Circle(color = BLUE)
        # c.generate_target()
        # c.target.shift(UP*2,RIGHT*3).scale(1/2)
        # c.target.set_fill(color = RED,opacity = 0.5)
        # self.add(c)
        # self.wait(1)
        # self.play(MoveToTarget(c),run_time=2)
        # self.wait(1)
        # self.play(c.animate.set_color(GREEN),run_time=2)

        # s = Square(color = BLUE)
        # s.save_state()
        # self.play(FadeIn(s))
        # self.play(s.animate.set_color(RED).shift(UP*2).scale(2),run_time=2)
        # self.play(Rotate(s,PI*2),s.animate.shift(DOWN*2),run_time=2)
        # self.play(Restore(s),run_time=2)

        t = Text("this is a caption",color = BLUE,font_size=24)
        self.add(t)
        s = Square(color = GREEN)
        self.play(Write(t.to_edge(DOWN),run_time=3),Create(s,run_time=3))
        self.play(FadeOut(t,run_time=0.3),Write(Text("Now we are done",color = GREEN,font_size=24).to_edge(DOWN),run_time = 5))
        
class SimpleCustomAnimation(Scene):
    def construct(self):
        def spiral_out(mobject,time):
            radius = time*4
            angle = 2*time*2*PI
            mobject.move_to(radius*(np.cos(angle)*RIGHT+np.sin(angle)*UP))
            # 计算颜色值
            r = int(255 * (0.5 + 0.5 * np.sin(time * 2 * PI)))  # 红色分量随时间变化
            g = int(255 * (0.5 + 0.5 * np.sin(time * 2 * PI + 2 * PI / 3)))  # 绿色分量
            b = int(255 * (0.5 + 0.5 * np.sin(time * 2 * PI + 4 * PI / 3)))  # 蓝色分量
            mobject.set_color((r, g, b))
            '''
                there are some issues here:
                    nomatter how I set the color,it always turns to blue.
                    the change of color is only form light color to dark color.
            '''

            mobject.set_opacity(1)
            mobject.set_fill(opacity = time)
        d = Dot(color = RED)
        self.add(d)
        self.play(UpdateFromAlphaFunc(d,spiral_out),run_time=3)

class Disperse(Animation):
    def __init__(self,mobject,dot_radius=0.05,dot_number = 100,**kwargs):
        super().__init__(mobject,**kwargs)
        self.dot_radius = dot_radius
        self.dot_number = dot_number

    def begin(self):
        dots = VGroup(*[Dot(radius=self.dot_radius).move_to(self.mobject.point_from_proportion(p))
                for p in np.linspace(0,1,self.dot_number)]
        )
        for dot in dots:
            dot.initial_position = dot.get_center()
            dot.shift_vector = 2*(dot.get_center()-self.mobject.get_center())
        dots.set_opacity(0)
        self.mobject.add(dots)
        self.dots = dots
        super().begin() 


    def clean_up_from_scene(self, scene: Scene) -> None:
        super().clean_up_from_scene(scene)
        scene.remove(self.dots)

    def interpolate_mobject(self, alpha: float) -> None:
        if alpha <= 0.5:
            self.mobject.set_opacity(1-alpha*2,family = False)
            self.dots.set_opacity(alpha*2)
        else:
            self.mobject.set_opacity(0)
            self.dots.set_opacity(2*(1-alpha))
            for dot in self.dots:
                dot.move_to(dot.initial_position + 2*(alpha-0.5)*dot.shift_vector)



# class CustomAnimation(Scene):

    # def construct(self):
        # stars = Star(color = YELLOW, fill_opacity=1).scale(3)
        # self.add(stars)
        # self.wait(1)
        # self.play(Disperse(stars,dot_number = 200,run_time=3))


        # star = Star(color = YELLOW,fill_opacity=1).scale(3)
        # dots = VGroup(*[Dot(radius=0.05).move_to(star.point_from_proportion(p)) 
        #     for p in np.linspace(0,1,200)]
        #     )
        # for dot in dots:
        #     dot.initial_position = dot.get_center()
        #     dot.shift_vector = 2*(dot.get_center())


        # self.play(*[dot.animate.move_to(star.point_from_proportion(1-i/200)) for i ,dot in enumerate(dots)],run_time=3)
        # enumrate is a build-in function in python,it can switch iterator to index and value.
        # we can use like this:
        # for i,dot in enumerate(dots):
        #     i is ths index of the dot
        #     dot is the dot itself.(value of the iterator)


        # use add_updater can connect two items toghter and update them together.
        # circle = Circle(color = BLUE,fill_opacity=1)
        # text = Text("Hello World",font_size=24,color = RED)
        # square = Square(color = GREEN,fill_opacity=1)

        # square.add_updater(lambda m: m.next_to(circle,RIGHT,buff=0.5))
        # circle.add_updater(lambda m: m.next_to(text,DOWN,buff=0.5))
        # self.add(circle,text,square)
        # self.wait(1)
        # self.play(text.animate.shift(UP*2))
        # self.wait(1)


# class name(Scene):
    def construct(self):
        c = Circle(color = RED,fill_opacity = 0.3,radius = 0.5)
        s = SurroundingRectangle(c,color = BLUE,corner_radius=0.1)
        t = Text("Manim").next_to(s,UP,buff = 0.5)

        self.play(Write(c),DrawBorderThenFill(s),Write(t))

        group = VGroup(c,s,t)
        csgroup = VGroup(c,s)
        self.play(t.animate.move_to([-4,0,0]),csgroup.animate.move_to([4,0,0]))

        arrow = always_redraw(lambda: Line(buff = 0.5,start = csgroup.get_left(),end = t.get_right(),color = WHITE,stroke_width = 2).add_tip(at_start = True,tip_shape = StealthTip).add_tip(tip_shape = StealthTip))

        self.play(Write(arrow))

        self.play(Indicate(t,scale = 1.5,color = ORANGE))
        self.play(Rotate(s,rangel = PI/2),ScaleInPlace(c,2))
        self.play(csgroup.animate.move_to([0,0,0]))

        self.play(FadeOut(arrow),FadeOut(t),run_time = 0.4)
        self.play(ShrinkToCenter(s),ScaleInPlace(c,30))
        self.play(FadeOut(c))

        self.wait()
        
        k = Text("Bye",font_size=48)
        self.play(Write(k))
        self.play(Unwrite(k))


class Test(Scene):
    def construct(self):
        t1 = Text("Hello ")
        t2 = Text("there")
        t3 = Text("d")
        t4 = Text("o")
        t5 = Text("g")
        group = VGroup(t1,t2,t3,t4,t5).arrange(RIGHT)
        group[3:5].shift(0.1*DOWN)

        group[2].set_color(RED)
        group[3].set_color(BLUE)
        group[4].set_color(ORANGE)


        # here can not use Text,we should use Tex instead..
        c = Circle(color = RED,radius = 0.3)
        p = RegularPolygon(5,color = GREEN)

        self.play(Write(group[2:]),run_time = 1)
        self.play(FadeIn(group[0:2]),run_time = 1)

        self.play(t1.animate.to_edge(UL,buff = 1),run_time = 1)
        self.play(t2.animate.to_edge(UR,buff = 1),run_time = 1)
 
        self.play(t3.animate.move_to([0,2,0]))
        self.play(t4.animate.move_to([0,0,0]))
        self.play(t5.animate.move_to([0,-2,0]))

        c = Circle(color = RED,radius = 0.5).move_to(t4.get_center())
        p = RegularPolygon(5,color = GREEN).scale(0.5).move_to(t3.get_center())
        s = Square(color = BLUE,fill_opacity = 0.5).scale(0.5).move_to(t5.get_center())

        self.play(SpinInFromNothing(s),SpinInFromNothing(p),GrowFromCenter(c),run_time = 2)
        self.play(Rotate(group[2:5],PI*4),Rotate(VGroup(p,s),PI*4),run_time = 1)

        pgroup = VGroup(p,t3)
        sgroup = VGroup(s,t5)

        self.play(Swap(pgroup,sgroup))

        Tx = Text("Bye")
        ggroup = Group(group,c,p,s)
        self.play(ReplacementTransform(ggroup,Tx),run_time = 0.5)

        self.play(FadeOut(Tx),run_time = 2)

        self.wait(1)

class Test2(Scene):
    def construct(self):

        plane = NumberPlane()
        axes = Axes(x_range=(-10,10),y_range=(-5,5),tips = False,x_length=13,y_length=7).add_coordinates()
        x = axes.get_x_axis_label("x")
        y = axes.get_y_axis_label("y") #if we use it,we should be support by latex.
        tri = Triangle(color = GREEN,fill_opacity = 0.5).move_to(axes.c2p(-3,4))

        dot = Dot(color = RED,radius = 0.1)
        dot_label = always_redraw(lambda:Text("Dot",font_size = 14).next_to(dot,DOWN,buff = 0.1))
  
        self.play(Write(axes),plane.animate,run_time = 2)
        self.play(Write(tri),Write(dot),Write(dot_label),run_time = 2)

        self.play(dot.animate.move_to(axes.c2p(7,-3)),run_time = 1)

        dot_label.clear_updaters()  # the function of clear_updaters is to remove alla the updaters of the dot_label
        # if we don't clear the updaters,the dot_label will always be redraw aslong as before (392),the font_size of dot_label will not change.

        group = VGroup(axes,tri,dot,dot_label)

        self.play(group.animate.scale(0.3).to_edge(UL),run_time = 2)

class Test3(Scene):
    def construct(self):
        t = ValueTracker(0)
        num = always_redraw(lambda: DecimalNumber(t.get_value(),num_decimal_places = 2))
        self.play(num.animate)
        self.play(t.animate.set_value(30),run_time = 3)
        self.wait(3)

class Test4(Scene):
    def construct(self):
        axes = Axes(x_range=(-10,10),y_range=(-5,5),tips = False,x_length=13,y_length=7).add_coordinates()
        x = axes.get_x_axis_label("x")
        y = axes.get_y_axis_label("y") 
        self.play(Write(axes),Write(x),Write(y))
        num = ValueTracker(1)

        curve = always_redraw(lambda:axes.plot(lambda x:np.sin(x*num.get_value())*num.get_value(),color = GREEN,stroke_width = 5))

        
        self.play(Create(curve),run_time = 2)
        for i in range(10):
            self.play(num.animate.set_value(3),run_time = 2)
            self.play(num.animate.set_value(0.3),run_time = 2)
            self.play(num.animate.set_value(30),run_time = 2)

        self.wait(3)

class Test5(Scene):
    def construct(self):
        a = Text("manmal")
        b = Text("manim")

        g = VGroup(a,b)
        g.arrange(DOWN,buff =4,aligned_edge = LEFT)
        self.play(Write(a))
        self.play(TransformMatchingShapes(a,b))

class Test6(Scene):
    def construct(self):
        c = Circle(color = RED).scale(0.1)
        c.set_fill(opacity = 1,color = WHITE)
        c.set_stroke(color = ORANGE,width = 7)

        s = SurroundingRectangle(c,color = RED,corner_radius=0.1)

        t = Text("Hello there",font_size=32,font = "Sentient")
        t[0:5].set_color(GOLD)
        t[5:11].set_color(TEAL)

        cs = VGroup(c,s)
        cst = VGroup(cs,t).arrange(RIGHT)
        cstt = VGroup(cs,t)

        self.play(GrowFromCenter(c),SpinInFromNothing(s))
        self.play(Write(t))

        square = Square(color = WHITE,side_length=1.2).shift(RIGHT*0.90)
        self.play(Write(square))

        tsquare  = VGroup(t[5:11],square)
        self.play(cs.animate.next_to(t[0:5],UP))
        self.play(tsquare.animate.next_to(t[0:5],DOWN))

        # if the mobject will be moved by more then 2 times in one play,we should adject the correct order.
        self.play(square.animate.scale(3).move_to(ORIGIN),cstt.animate.move_to(ORIGIN),t[5:].animate.move_to(ORIGIN).shift(DOWN*0.3),run_time = 1)

        dot =Dot(color = WHITE)

        ggroup = VGroup(cst,square)
        self.play(Transform(ggroup,dot))
        self.play(ScaleInPlace(ggroup,300),run_time = 1)
        self.play(FadeOut(ggroup),run_time =1)
    
class Test7(Scene):
    def construct(self):
        # def rotate(mobject,time):
        #     angle = 2*time*PI
        #     radius = 2*time
        #     mobject.set_color(color = GREEN)
        #     mobject.move_to(radius*np.cos(angle*3)*RIGHT+radius*np.sin(angle*3)*UP)

        # dot = Dot(color = RED)
        # self.add(dot)
        # self.play(UpdateFromAlphaFunc(dot,rotate),run_time = 2)
        # c = Circle(color = RED)
        # s = Square(color = GREEN).to_edge(LEFT)
        # self.play(GrowFromCenter(c),run_time = 2)
        # self.play(Transform(c.copy(),s))

        # coordinate latex we can write formula like this:
        t = Tex('$\\alpha \\beta \zeta 5\\frac{3}{4}$')
        self.play(Write(t))

class Test8(Scene):
    def construct(self):
        def update_curve(mobject,t):
            radius = 2*t
            angle = 2*t*PI
            mobject.set_color(color = GOLD)
            mobject.move_to(radius*np.cos(angle*t*3)*RIGHT+radius*np.sin(angle*t*3)*UP)

        c = Circle(color = RED).scale(0.1)
        c.set_fill(opacity = 1,color = WHITE)
        c.set_stroke(color = ORANGE,width = 7)

        s = SurroundingRectangle(c,color = RED,corner_radius=0.1)

        t = Text("Hello there",font_size=32,font = "Sentient")
        t[0:5].set_color(GOLD)
        t[5:11].set_color(TEAL)

        cs = VGroup(c,s)
        cst = VGroup(cs,t).arrange(RIGHT)
        cstt = VGroup(cs,t)

        self.play(GrowFromCenter(c),SpinInFromNothing(s))
        self.play(Write(t))

        square = Square(color = WHITE,side_length=1.2).shift(RIGHT*0.90)
        self.play(Write(square))

        tsquare  = VGroup(t[5:11],square)
        self.play(cs.animate.next_to(t[0:5],UP))
        self.play(tsquare.animate.next_to(t[0:5],DOWN))

        # if the mobject will be moved by more then 2 times in one play,we should adject the correct order.
        self.play(square.animate.scale(3).move_to(ORIGIN),cstt.animate.move_to(ORIGIN),t[5:].animate.move_to(ORIGIN).shift(DOWN*0.3),run_time = 1)

        dot =Dot(color = WHITE)

        ggroup = VGroup(cst,square)
        self.play(Transform(ggroup,dot))
        self.play(ScaleInPlace(ggroup,300),run_time = 1)
        self.play(FadeOut(ggroup),run_time =1)

        c = Circle(color = RED,fill_opacity = 0.3,radius = 0.5)
        s = SurroundingRectangle(c,color = BLUE,corner_radius=0.1)
        t = Text("Manim").next_to(s,UP,buff = 0.5)

        self.play(Write(c),DrawBorderThenFill(s),Write(t))

        group = VGroup(c,s,t)
        csgroup = VGroup(c,s)
        self.play(t.animate.move_to([-4,0,0]),csgroup.animate.move_to([4,0,0]))

        arrow = always_redraw(lambda: Line(buff = 0.5,start = csgroup.get_left(),end = t.get_right(),color = WHITE,stroke_width = 2).add_tip(at_start = True,tip_shape = StealthTip).add_tip(tip_shape = StealthTip))

        self.play(Write(arrow))

        self.play(Indicate(t,scale = 1.5,color = ORANGE))
        self.play(Rotate(s,rangel = PI/2),ScaleInPlace(c,2))
        self.play(csgroup.animate.move_to([0,0,0]))

        self.play(FadeOut(arrow),FadeOut(t),run_time = 0.4)
        self.play(ShrinkToCenter(s),ScaleInPlace(c,30))
        self.play(FadeOut(c))

        self.wait()

        t = Text("Now we show something instereting").to_edge(DOWN)
        s = Square(color = BLUE,fill_opacity = 0.5).scale(0.5)
        c = Circle(color = RED,radius = 0.5,fill_opacity = 0.4)
        self.play(SpinInFromNothing(s,run_time = 2),Write(t,run_time = 1))
        self.play(ReplacementTransform(s,c,run_time = 2),Unwrite(t,run_time = 1))

        self.play(UpdateFromAlphaFunc(c,update_curve))
        self.play(c.animate.move_to(ORIGIN))
        self.wait(2)
        t = Text("That'all,bye!",font_size = 48)
        self.play(ShrinkToCenter(c),run_time = 1)
        self.play(Write(t))

        self.wait(2)