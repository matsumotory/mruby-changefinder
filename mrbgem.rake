MRuby::Gem::Specification.new('mruby-changefinder') do |spec|
  spec.license = 'MIT'
  spec.authors = 'MATSUMOTO Ryosuke'
  spec.version = '0.0.1'
  spec.summary = 'Detect change point via continuous outlier and smoothing'
  spec.add_dependency 'mruby-matrix', github: 'matsumoto-r/mruby-matrix'
  spec.add_dependency 'mruby-mtest'
  spec.add_dependency 'mruby-random', core: 'mruby-random'
  spec.add_dependency 'mruby-numeric-ext', core: 'mruby-numeric-ext'
  spec.add_dependency 'mruby-enumerator', core: 'mruby-enumerator'
end
