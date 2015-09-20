/*
 * main.c
 * Sets up the Window, ClickConfigProvider and ClickHandlers.
 */

#include <pebble.h>
int volatile w = 0;
int maxPulse = 2000;
static Window *s_main_window;
static TextLayer *s_output_layer;

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(s_output_layer, "Up pressed!");w = maxPulse;
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(s_output_layer, "Select pressed!");w = maxPulse;
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(s_output_layer, "Down pressed!");w = maxPulse;
}

static void click_config_provider(void *context) {
  // Register the ClickHandlers
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);

  // Create output TextLayer
  s_output_layer = text_layer_create(GRect(5, 0, window_bounds.size.w - 5, window_bounds.size.h));
  text_layer_set_font(s_output_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text(s_output_layer, "WakeUp !!");
  text_layer_set_overflow_mode(s_output_layer, GTextOverflowModeWordWrap);
  layer_add_child(window_layer, text_layer_get_layer(s_output_layer));
}

static void main_window_unload(Window *window) {
  // Destroy output TextLayer
  text_layer_destroy(s_output_layer);
}

static void init() {
  // Create main Window
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  window_set_click_config_provider(s_main_window, click_config_provider);
  window_stack_push(s_main_window, true);
}

static void deinit() {
  // Destroy main Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  while(w<maxPulse){
    vibes_long_pulse();
     app_event_loop();
  }
 
  deinit();
}