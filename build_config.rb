MRuby::Build.new do |conf|
  toolchain :gcc

  # include the default GEMs
  conf.gembox 'full-core'
  conf.gem File.expand_path(File.dirname(__FILE__))
  conf.gem :github => 'matsumoto-r/mruby-sleep'
  conf.enable_test
end

