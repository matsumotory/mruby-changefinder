# mruby-changefinder   [![Build Status](https://travis-ci.org/matsumoto-r/mruby-changefinder.png?branch=master)](https://travis-ci.org/matsumoto-r/mruby-changefinder)
ChangeFinder class
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'matsumoto-r/mruby-changefinder'
end
```
## example
```ruby
# ChangeFinder.new sdar_order_for_outlier, outlier_discount_param, sdar_order_for_change_point, change_point_discount_param, smooth_term
> cf = ChangeFinder.new 3, 0.1, 3, 0.1, 5
 => #<ChangeFinder:0x7fad5c80be50 @ts_data_buffer=[], @change_point_analyze=#<ChangeFinder::SDAR:0x7fad5c80bb80>, @smooth_term=5, @outlier_analyze=#<ChangeFinder::SDAR:0x7fad5c80be20>>
> cf.learn [1,2,1,2,3,2,1,2,1]
 => [6.2017912433901, 1.3973555597559, 2.4211198000217, 2.3979400886673, 1.7835503570548, 1.4166612339939, 1.4837836144657, 1.2835583707215, 1.1556254255408]
> cf.score 1
 => 1.1044914205061
>
```

## License
under the MIT License:
- see LICENSE file
