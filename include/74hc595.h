typedef struct sr_74hc595_t {
    int clk_pin;
    int data_pin;
    int latch_pin;
    unsigned int pins;

    void (*fn_gpio_put)(int, bool);
    void (*fn_sleep_us)(int);
} sr_74hc595_t;

void clock_signal(sr_74hc595_t *sr) {
    sr->fn_gpio_put(sr->clk_pin, 1);
    sr->fn_sleep_us(5);
    sr->fn_gpio_put(sr->clk_pin, 0);
    sr->fn_sleep_us(5);
};

void trigger_latch(sr_74hc595_t *sr) {
    sr->fn_gpio_put(sr->latch_pin, 1);
    sr->fn_sleep_us(5);
    sr->fn_gpio_put(sr->latch_pin, 0);
}

// Send data synchronously in least significant bit order and trigger storage register latch
void write(sr_74hc595_t *sr, int data) {
    int i;
    for (i = 0; i < 8; i++) {
        sr->fn_gpio_put(sr->data_pin, (data >> i) & (0x01));
        clock_signal(sr);
    }
    trigger_latch(sr);
}