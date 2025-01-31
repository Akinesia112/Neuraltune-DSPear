class Equalizer {
public:
    Equalizer(double lowGain, double midGain, double highGain);
    double process(double input);

    void setLowGain(double gain);
    void setMidGain(double gain);
    void setHighGain(double gain);

private:
    double lowGain, midGain, highGain;
};

class Limiter {
public:
    Limiter(double threshold);
    double process(double input);

    void setThreshold(double threshold);

private:
    double threshold;
};
