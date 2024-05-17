extends TextEdit

## Controls how many seconds elapses between inserting each new character
## of ELIZA's answer.
@export var output_pace: float = 0.07

var input_start: int
var user_input: String
var eliza_answer: String
var last_line_count: int
var currently_printing: bool = false


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	grab_focus.call_deferred()
	await eliza_print($ELIZA.hello_message)
	input_start = text.length()
	last_line_count = get_line_count()


func _input(event: InputEvent) -> void:
	if event.is_action_pressed("ui_text_newline"):
		# Trim to the actual sentance and remove newline at the end.
		user_input = text.substr(input_start, -1)
		if user_input.length() >= 2:
			user_input[-1] = ""

		eliza_answer = $ELIZA.answer(user_input)
		await eliza_print('\n' +  eliza_answer)

		last_line_count = get_line_count()
		input_start = text.length()

		set_caret_line(get_line_count() - 1)
		set_caret_column(0)


func _on_text_changed() -> void:
	# The user could not delete lines
	if get_line_count() < last_line_count:
		text += '\n'
		set_caret_line(get_line_count() - 1)
		return


func eliza_print(s: String):
		# Simple lock against simultaneus calls
		if currently_printing:
			return
		else:
			currently_printing = true

		editable = false
		var caret_column = get_caret_column()
		var t = get_tree()

		for c in s.split(""):
			await t.create_timer(output_pace).timeout
			text += c

			set_caret_line(get_line_count() - 1)

			caret_column += 1
			set_caret_column(caret_column)

		text += "\n\n"

		editable = true
		currently_printing = false


func _on_focus_entered() -> void:
		set_caret_line(get_line_count() - 1)
		set_caret_column(0)


# Caret is always on the last line
func _on_caret_changed() -> void:
	if get_caret_line() < (get_line_count() - 1):
		set_caret_line(get_line_count() - 1)
