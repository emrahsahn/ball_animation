# ball animation
import tkinter as tk
import random


class Ball:
    def __init__(self, canvas, size, color, speed):
        self.canvas = canvas
        self.size = size

        self.color = color
        self.speed = speed
        self.is_running = False  # Animasyonun durdurulup durdurulmadığını kontrol eden bayrak

        self.dx = random.choice([-1,1]) * self.speed
        self.dy = random.choice([-1,1]) * self.speed

        x = random.randint(size, 400 - size)
        y = random.randint(size, 300 - size)
        self.id = self.canvas.create_oval(x - size, y - size, x + size, y + size, fill=self.color)

    def move(self):
        x1, y1, x2, y2 = self.canvas.coords(self.id)

        if x1 <= 0 or x2 >= 400:
            self.dx = -self.dx
        if y1 <= 0 or y2 >= 300:
            self.dy = -self.dy

        self.canvas.move(self.id, self.dx, self.dy)

class BallAnimation:
    def __init__(self, frame):
        self.frame = frame
        self.frame.title("Ball Animation")

        # Başlangıç değerleri
        self.selected_color = "gray"
        self.speed = 2
        self.balls = []
        self.is_running = False  # Animasyonun hareket durumunu kontrol eden bayrak

        self.canvas = tk.Canvas(frame, width=400, height=300, bg='lightgray')
        self.canvas.pack()

        main_frame = tk.Frame(frame)
        main_frame.pack()


        # renk butonları
        red_button = tk.Button(main_frame, bg='red', width=5, height=2, command=lambda: self.take_color("red"))
        red_button.grid(row=1, column=0, padx=5, pady=5)

        blue_button = tk.Button(main_frame, bg='blue', width=5, height=2, command=lambda: self.take_color("blue"))
        blue_button.grid(row=1, column=1, padx=5, pady=5)

        yellow_button = tk.Button(main_frame, bg='yellow', width=5, height=2, command=lambda: self.take_color("yellow"))
        yellow_button.grid(row=1, column=2, padx=5, pady=5)

        # start, stop, reset, hızlandırma butonları
        start_button = tk.Button(main_frame, text="Start", bg="white", width=10, height=2, command=self.start_animation)
        start_button.grid(row=2, column=0, padx=5, pady=5)

        stop_button = tk.Button(main_frame, text="Stop", bg="white", width=10, height=2, command=self.stop_animation)
        stop_button.grid(row=2, column=1, padx=5, pady=5)

        reset_button = tk.Button(main_frame, text="Reset", bg="white", width=10, height=2, command=self.reset_canvas)
        reset_button.grid(row=2, column=2, padx=5, pady=5)

        speedup_button = tk.Button(main_frame, text="Speedup", bg="white", width=10, height=2, command=self.speed_up)
        speedup_button.grid(row=2, column=3, padx=5, pady=5)


        # boyut butonları
        self.create_circle_button(main_frame, 10, 0, 0)
        self.create_circle_button(main_frame, 20, 0, 1)
        self.create_circle_button(main_frame, 30, 0, 2)


    def create_circle_button(self, frame, size, row, column):
        circle_canvas = tk.Canvas(frame, width=size*2, height=size * 2, bg="white", highlightthickness=0)
        circle_canvas.grid(row=row, column=column, padx=10, pady=10)
        circle_canvas.create_oval(2, 2, size*2-2, size*2-2, fill=self.selected_color)

        circle_canvas.bind("<Button-1>", lambda event, s=size: self.add_ball(s,self.selected_color))

    def add_ball(self, size, color):
        '''Ball sınıfı sayesinde ekrana top eklenir'''
        ball = Ball(self.canvas, size, color, self.speed)
        self.balls.append(ball)

    def take_color(self, color):
        self.selected_color = color

    def start_animation(self):
        if not self.is_running:
            self.is_running = True
            self.animate()

    def animate(self):
        if self.is_running:
            for ball in self.balls:
                ball.move()
            self.frame.after(20, self.animate)

    def stop_animation(self):
        self.is_running = False

    def reset_canvas(self):
        self.canvas.delete("all")
        self.balls.clear()
        self.is_running = False

    def speed_up(self):
        # Hızı artır ve mevcut topların hızlarını güncelle
        self.speed += 1
        for ball in self.balls:
            ball.dx = self.speed if ball.dx > 0 else -self.speed
            ball.dy = self.speed if ball.dy > 0 else -self.speed


root = tk.Tk()
app = BallAnimation(root)
root.mainloop()


