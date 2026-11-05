"""Render one animated GIF per easing curve for the README.

The values come from the C++ header itself, via the plot example:

    easings_plot --csv > curves.csv
    python tools/make_gifs.py curves.csv doc

Each GIF shows a dot moving along a track at the eased speed, with a short
trail, and a small grey dot above it moving at constant speed for reference.
Colours and size match the curve PNGs in doc/.

Needs Pillow (pip install pillow).
"""

import argparse
import csv
import sys
from collections import defaultdict
from pathlib import Path

from PIL import Image, ImageDraw, ImageFont

SIZE = 190
BACKGROUND = (30, 30, 30)
FOREGROUND = (230, 230, 230)
TRACK = (82, 82, 82)
LINEAR = (110, 110, 110)
MARGIN = 18
TRACK_Y = 105
LINEAR_Y = 70
DOT_RADIUS = 7
TRAIL = 6

FRAME_MS = 25
HOLD_START_MS = 400
HOLD_END_MS = 700


def read_curves(stream):
    curves = defaultdict(list)
    for row in csv.DictReader(stream):
        curves[row["curve"]].append(float(row["y"]))
    return curves


def blend(colour, weight):
    return tuple(round(b + (c - b) * weight) for c, b in zip(colour, BACKGROUND))


def render(name, values, font):
    # the track spans 0..1 and shrinks only as far as this curve overshoots
    lowest, highest = min(0.0, *values), max(1.0, *values)

    def to_x(value):
        return MARGIN + (value - lowest) / (highest - lowest) * (SIZE - 2 * MARGIN)

    frames = []
    steps = len(values) - 1

    for index, value in enumerate(values):
        image = Image.new("RGB", (SIZE, SIZE), BACKGROUND)
        draw = ImageDraw.Draw(image)

        # track from 0 to 1 with end ticks
        start, end = to_x(0.0), to_x(1.0)
        draw.line([(start, TRACK_Y), (end, TRACK_Y)], fill=TRACK, width=1)
        for tick in (start, end):
            draw.line([(tick, TRACK_Y - 5), (tick, TRACK_Y + 5)], fill=TRACK, width=1)

        # linear reference
        linear_x = to_x(index / steps)
        draw.line([(start, LINEAR_Y), (end, LINEAR_Y)], fill=blend(TRACK, 0.5), width=1)
        draw.ellipse([linear_x - 3, LINEAR_Y - 3, linear_x + 3, LINEAR_Y + 3], fill=LINEAR)

        # trail, oldest first so the newest sits on top
        for age in range(TRAIL, 0, -1):
            if index - age < 0:
                continue
            x = to_x(values[index - age])
            radius = DOT_RADIUS * (1 - age / (TRAIL + 2))
            colour = blend(FOREGROUND, 0.45 * (1 - age / (TRAIL + 1)))
            draw.ellipse([x - radius, TRACK_Y - radius, x + radius, TRACK_Y + radius], fill=colour)

        x = to_x(value)
        draw.ellipse([x - DOT_RADIUS, TRACK_Y - DOT_RADIUS, x + DOT_RADIUS, TRACK_Y + DOT_RADIUS], fill=FOREGROUND)

        draw.text((SIZE / 2, SIZE - 12), name, fill=FOREGROUND, font=font, anchor="ms")
        frames.append(image.quantize(colors=32))

    durations = [FRAME_MS] * len(frames)
    durations[0] = HOLD_START_MS
    durations[-1] = HOLD_END_MS
    return frames, durations


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("csv", help="output of 'easings_plot --csv', or - for stdin")
    parser.add_argument("out_dir", type=Path, help="where to write <curve>.gif")
    args = parser.parse_args()

    if args.csv == "-":
        curves = read_curves(sys.stdin)
    else:
        with open(args.csv, newline="", encoding="utf-8") as stream:
            curves = read_curves(stream)

    if not curves:
        sys.exit("no curves in input")

    font = ImageFont.load_default(size=13)

    args.out_dir.mkdir(parents=True, exist_ok=True)
    for name, values in curves.items():
        frames, durations = render(name, values, font)
        path = args.out_dir / f"{name}.gif"
        frames[0].save(path, save_all=True, append_images=frames[1:], duration=durations, loop=0, optimize=True)
        print(f"{path} ({path.stat().st_size // 1024} KB)")


if __name__ == "__main__":
    main()
