extends Label


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass


func _on_button_pressed() -> void:
	text = %ELIZA.answer("I feel great")


func _on_line_edit_text_submitted(new_text: String) -> void:
	text = %ELIZA.answer(new_text)
	%ELIZAInput.text = ""
