extends MeshInstance3D

func _unhandled_input(event: InputEvent) -> void:
	$SubViewport.push_input(event)
