import json
import os

try:
    import bpy
except ImportError:
    raise SystemExit("This script must be run inside Blender's Python environment.")


def safe_value(value):
    if value is None:
        return None
    if isinstance(value, (int, float, str, bool)):
        return value
    if hasattr(value, "__iter__") and not isinstance(value, (str, bytes)):
        try:
            return list(value)
        except Exception:
            pass
    return str(value)


def export_scene_node_tree(scene, out_path):
    tree = getattr(scene, "node_tree", None)
    if tree is None:
        scene.use_nodes = True
        tree = scene.node_tree

    if tree is None:
        raise RuntimeError(f"Scene '{scene.name}' has no compositor node tree.")

    nodes = []
    for n in tree.nodes:
        node = {
            "name": n.name,
            "type": n.type,
            "bl_idname": n.bl_idname,
            "location": [float(n.location.x), float(n.location.y)],
            "label": n.label,
            "inputs": [],
            "outputs": [],
        }

        for s in n.inputs:
            node["inputs"].append({
                "name": s.name,
                "type": getattr(getattr(s, "bl_rna", None), "name", "socket"),
                "default_value": safe_value(getattr(s, "default_value", None)),
            })

        for s in n.outputs:
            node["outputs"].append({
                "name": s.name,
                "type": getattr(getattr(s, "bl_rna", None), "name", "socket"),
            })

        nodes.append(node)

    links = []
    for l in tree.links:
        links.append({
            "from_node": l.from_node.name,
            "from_socket": l.from_socket.name,
            "to_node": l.to_node.name,
            "to_socket": l.to_socket.name,
        })

    data = {
        "scene": scene.name,
        "nodes": nodes,
        "links": links,
    }

    with open(out_path, "w", encoding="utf-8") as f:
        json.dump(data, f, ensure_ascii=False, indent=2)

    print(f"Exported compositor graph for scene '{scene.name}' to: {out_path}")


out_dir = os.path.dirname(bpy.data.filepath) or os.getcwd()
out_path = os.path.join(out_dir, "blend_node_graph.json")

if not bpy.data.scenes:
    raise RuntimeError("No scenes found in this Blender file.")

for scene in bpy.data.scenes:
    export_scene_node_tree(scene, out_path)

print("Done.")
