class ChangeFinder
  class Utils
    class << self
      def smooth ts_data, smooth_term
        _end = ts_data.size
        _begin = [_end - smooth_term, 0].max
        (_size = (_end - _begin)) == 0 ? 0.0 : ts_data.slice(_begin, _end).inject(:+).to_f / _size
      end
    end
  end
end
