#include "clock.hpp"

void clockTime::updateTime() {
  uint64_t new_seconds = now_us()/1e6;
  if (new_seconds >= total_seconds) {
    total_seconds++;
    seconds++;
  }
  if (seconds >= 60) {
    minutes++;
    seconds = 0;
  }
  if (minutes >= 60) {
    hours++;
    minutes = 0;
  }
  if (hours > 11) {
    hours = 0;
  }
}

void clockTime::updateButton() {
  but_hour_up.refresh();
  but_min_up.refresh();
  if (!but_hour_up.read()) {
    hours++;
  }
  if (!but_min_up.read()) {
    minutes++;
  }
}

void clockBase::draw(window& w) {
  for (int i = 0; i < 360; i++) {
    int x_scaled = sin_tab.get(i) * radius;
    int y_scaled = cos_tab.get(i) * radius * -1;
    xy draw_pos = xy(x_scaled, y_scaled) + start;
    w.write(draw_pos);
  }
  for (int i = 0; i < 12; i++) {
    int x_pos = sin_tab.get(i * 30) * (radius - dist_dot);
    int y_pos = cos_tab.get(i * 30) * (radius - dist_dot) * -1;
    xy draw_pos = xy(x_pos, y_pos) + start;
    w.write(draw_pos);
  }
}

void clockArm::draw(window& w) {
  if (update_needed) {
    line del_arm = line(start, old_end, color{0, 0, 0});
    del_arm.draw(w);
    int loc_table = time_val * deg_fac;
    int x_end = sin_tab.get(loc_table) * length;
    int y_end = cos_tab.get(loc_table) * length * -1;
    xy new_end = xy(x_end, y_end) + start;
    line new_arm = line(start, new_end);
    new_arm.draw(w);
    old_end = new_end;
  }
}

void clockArm::update(int new_time, bool update) {
  update_needed = (update || (time_val != new_time));
  time_val = new_time;
}

void analogClock::draw(window& w) {
  if (first_draw) {
    base.draw(w);
    first_draw = false;
    w.flush();
  }
  hour.draw(w);
  min.draw(w);
  sec.draw(w);
  w.flush();
}

void analogClock::updateClock(window& w) {
  bool min_updt = true;
  bool hour_updt = true;
  while (true) {

		updateButton();
    updateTime();

    sec.update(seconds, true);
    min.update(minutes, min_updt);
    hour.update(hours, hour_updt);
    
    draw(w);
  }
}