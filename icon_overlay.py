import os
import tgalib
import argparse


def get_iss_file(f):
    path = os.path.split(f)[0]
    name = os.path.basename(f).split("_")[1]
    return os.path.join(path, f"iss_{name}")


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('icon', help='TGA icon file')
    parser.add_argument('level', help='Overlay level')
    parser.add_argument('output', help='TGA icon output file', nargs="+")
    args = parser.parse_args()

    if not os.path.exists(args.icon):
        print(f"{args.icon} missing...")
        exit()

    overlay_tga_1 = f"{args.level}.tga"
    overlay_tga_2 = f"{args.level}_2.tga"

    if not os.path.exists(overlay_tga_1) or not os.path.exists(overlay_tga_2):
        print(f"Overlay tga file missing...")
        exit()

    icons = [args.icon]
    if len(icons) < 2 and "_" in icons[0] and os.path.exists(get_iss_file(icons[0])):
        icons.append(get_iss_file(icons[0]))

    outputs = args.output
    if len(icons) > 1:
        output_file = outputs[0]
        if "_" in output_file:
            outputs.append(get_iss_file(output_file))

    for i, icon in enumerate(icons):
        original = tgalib.Picture()
        original.ImportData(icon)
        overlay_1 = tgalib.Picture()
        overlay_1.ImportData(overlay_tga_1)
        overlay_2 = tgalib.Picture()
        overlay_2.ImportData(overlay_tga_2)

        final = tgalib.Picture().ScreenBlend(original, overlay_1)
        if "iss" not in icon:
            final = tgalib.Picture().MultiplyBlend(final, overlay_2)
        print(f"Overlaying {icon} to {outputs[i]}")
        final.ExportData(outputs[i])
