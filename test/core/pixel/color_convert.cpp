#include <boost/gil/cmyk.hpp>
#include <boost/gil/gray.hpp>
#include <boost/gil/pixel.hpp>

#include <boost/gil/rgb.hpp>

#include <boost/mp11.hpp>
#include <boost/core/lightweight_test.hpp>

#include "test_fixture.hpp"
#include "core/channel/test_fixture.hpp"

namespace gil = boost::gil;
namespace fixture = boost::gil::test::fixture;
namespace mp11 = boost::mp11;

template <typename SrcPixel>
struct test_rgb_from_gray
{
    template <typename DstPixel>
    void operator()(DstPixel const&)
    {
        using pixel_src_t = SrcPixel;
        using pixel_dst_t = DstPixel;
        fixture::channel_value<typename gil::channel_type<pixel_src_t>::type> f_src;
        fixture::channel_value<typename gil::channel_type<pixel_dst_t>::type> f_dst;

        // BLACK
        {
            pixel_src_t const src{f_src.min_v_};
            pixel_dst_t dst;
            gil::color_convert(src, dst);

            BOOST_TEST_EQ(gil::get_color(dst, gil::red_t{}), f_dst.min_v_);
            BOOST_TEST_EQ(gil::get_color(dst, gil::green_t{}), f_dst.min_v_);
            BOOST_TEST_EQ(gil::get_color(dst, gil::blue_t{}), f_dst.min_v_);
        }
        // WHITE
        {
            pixel_src_t const src{f_src.max_v_};
            pixel_dst_t dst;
            gil::color_convert(src, dst);

            BOOST_TEST_EQ(gil::get_color(dst, gil::red_t{}), f_dst.max_v_);
            BOOST_TEST_EQ(gil::get_color(dst, gil::green_t{}), f_dst.max_v_);
            BOOST_TEST_EQ(gil::get_color(dst, gil::blue_t{}), f_dst.max_v_);
        }
    }

    static void run()
    {
        boost::mp11::mp_for_each
        <
            mp11::mp_list
            <
                gil::rgb8_pixel_t,
                gil::rgb8s_pixel_t,
                gil::rgb16_pixel_t,
                gil::rgb16s_pixel_t,
                gil::rgb32_pixel_t,
                gil::rgb32s_pixel_t,
                gil::rgb32f_pixel_t
            >
        >(test_rgb_from_gray{});
    }
};

struct test_rgb_from_cmyk 
{
    template <typename SrcPixel, typename DstPixel>
    void operator()(mp11::mp_list<SrcPixel, DstPixel> const&) const
    {
        using pixel_src_t = SrcPixel;
        using pixel_dst_t = DstPixel;
        fixture::channel_value<typename gil::channel_type<pixel_src_t>::type> f_src;
        fixture::channel_value<typename gil::channel_type<pixel_dst_t>::type> f_dst;

        // BLACK
        {
            pixel_src_t const src{f_src.max_v_};
            pixel_dst_t dst;
            gil::color_convert(src, dst);

            BOOST_TEST_EQ(gil::get_color(dst, gil::red_t{}), f_dst.min_v_);
            BOOST_TEST_EQ(gil::get_color(dst, gil::green_t{}), f_dst.min_v_);
            BOOST_TEST_EQ(gil::get_color(dst, gil::blue_t{}), f_dst.min_v_);
        }

        // WHITE
        {
            pixel_src_t const src{f_src.min_v_};
            pixel_dst_t dst;
            gil::color_convert(src, dst);

            BOOST_TEST_EQ(gil::get_color(dst, gil::red_t{}), f_dst.max_v_);
            BOOST_TEST_EQ(gil::get_color(dst, gil::green_t{}), f_dst.max_v_);
            BOOST_TEST_EQ(gil::get_color(dst, gil::blue_t{}), f_dst.max_v_);
        }

        // CYAN
        {
            pixel_src_t const src{f_src.max_v_, f_src.min_v_, f_src.min_v_, f_src.min_v_};
            pixel_dst_t dst;
            gil::color_convert(src, dst);

            BOOST_TEST_EQ(gil::get_color(dst, gil::red_t{}), f_dst.min_v_);
            BOOST_TEST_EQ(gil::get_color(dst, gil::green_t{}), f_dst.max_v_);
            BOOST_TEST_EQ(gil::get_color(dst, gil::blue_t{}), f_dst.max_v_);
        }

        // MAGENTA
        {
            pixel_src_t const src{f_src.min_v_, f_src.max_v_, f_src.min_v_, f_src.min_v_};
            pixel_dst_t dst;
            gil::color_convert(src, dst);

            BOOST_TEST_EQ(gil::get_color(dst, gil::red_t{}), f_dst.max_v_);
            BOOST_TEST_EQ(gil::get_color(dst, gil::green_t{}), f_dst.min_v_);
            BOOST_TEST_EQ(gil::get_color(dst, gil::blue_t{}), f_dst.max_v_);
        }

        // YELLOW
        {
            pixel_src_t const src{f_src.min_v_, f_src.min_v_, f_src.max_v_, f_src.min_v_};
            pixel_dst_t dst;
            gil::color_convert(src, dst);

            BOOST_TEST_EQ(gil::get_color(dst, gil::red_t{}), f_dst.max_v_);
            BOOST_TEST_EQ(gil::get_color(dst, gil::green_t{}), f_dst.max_v_);
            BOOST_TEST_EQ(gil::get_color(dst, gil::blue_t{}), f_dst.min_v_);
        }

        // BLUE
        {
            pixel_src_t const src{f_src.max_v_, f_src.max_v_, f_src.min_v_, f_src.min_v_};
            pixel_dst_t dst;
            gil::color_convert(src, dst);

            BOOST_TEST_EQ(gil::get_color(dst, gil::red_t{}), f_dst.min_v_);
            BOOST_TEST_EQ(gil::get_color(dst, gil::green_t{}), f_dst.min_v_);
            BOOST_TEST_EQ(gil::get_color(dst, gil::blue_t{}), f_dst.max_v_);
        }

        // GREEN
        {
            pixel_src_t const src{f_src.max_v_, f_src.min_v_, f_src.max_v_, f_src.min_v_};
            pixel_dst_t dst;
            gil::color_convert(src, dst);

            BOOST_TEST_EQ(gil::get_color(dst, gil::red_t{}), f_dst.min_v_);
            BOOST_TEST_EQ(gil::get_color(dst, gil::green_t{}), f_dst.max_v_);
            BOOST_TEST_EQ(gil::get_color(dst, gil::blue_t{}), f_dst.min_v_);
        }

        // RED
        {
            pixel_src_t const src{f_src.min_v_, f_src.max_v_, f_src.max_v_, f_src.min_v_};
            pixel_dst_t dst;
            gil::color_convert(src, dst);

            BOOST_TEST_EQ(gil::get_color(dst, gil::red_t{}), f_dst.max_v_);
            BOOST_TEST_EQ(gil::get_color(dst, gil::green_t{}), f_dst.min_v_);
            BOOST_TEST_EQ(gil::get_color(dst, gil::blue_t{}), f_dst.min_v_);
        }
    }

    static void run()
    {
        boost::mp11::mp_for_each
        <
            mp11::mp_product
            <
                mp11::mp_list,
                mp11::mp_list
                <
                    gil::cmyk8_pixel_t,
                    gil::cmyk16_pixel_t,
                    gil::cmyk32_pixel_t,
                    gil::cmyk32f_pixel_t
                >,
                mp11::mp_list
                <
                    gil::rgb8_pixel_t,
                    gil::rgb8s_pixel_t,
                    gil::rgb16_pixel_t,
                    gil::rgb16s_pixel_t,
                    gil::rgb32_pixel_t,
                    gil::rgb32s_pixel_t,
                    gil::rgb32f_pixel_t
                >
            >
        >(test_rgb_from_cmyk{});
    }
};

template <typename SrcPixel>
struct test_gray_from_rgb
{
    template <typename DstPixel>
    void operator()(DstPixel const&)
    {
        using pixel_src_t = SrcPixel;
        using pixel_dst_t = DstPixel;
        fixture::channel_value<typename gil::channel_type<pixel_src_t>::type> f_src;
        fixture::channel_value<typename gil::channel_type<pixel_dst_t>::type> f_dst;

        // BLACK
        {
            pixel_src_t const src{f_src.min_v_};
            pixel_dst_t dst;
            gil::color_convert(src, dst);

            BOOST_TEST_EQ(gil::get_color(dst, gil::gray_color_t{}), f_dst.min_v_);
        }
        // WHITE
        {
            pixel_src_t const src{f_src.max_v_};
            pixel_dst_t dst;
            gil::color_convert(src, dst);

            BOOST_TEST_EQ(gil::get_color(dst, gil::gray_color_t{}), f_dst.max_v_);
        }
    }

    static void run()
    {
        boost::mp11::mp_for_each
        <
            mp11::mp_list
            <
                gil::gray8_pixel_t,
                gil::gray8s_pixel_t,
                gil::gray16_pixel_t,
                gil::gray16s_pixel_t,
                gil::gray32_pixel_t,
                gil::gray32s_pixel_t,
                gil::gray32f_pixel_t
            >
        >(test_gray_from_rgb<SrcPixel>{});
    }
};

template <typename SrcPixel>
struct test_gray_from_cmyk
{
    template <typename DstPixel>
    void operator()(DstPixel const&)
    {
        using pixel_src_t = SrcPixel;
        using pixel_dst_t = DstPixel;
        fixture::channel_value<typename gil::channel_type<pixel_src_t>::type> f_src;
        fixture::channel_value<typename gil::channel_type<pixel_dst_t>::type> f_dst;

        // BLACK
        {
            pixel_src_t const src{f_src.max_v_};
            pixel_dst_t dst;
            gil::color_convert(src, dst);

            BOOST_TEST_EQ(gil::get_color(dst, gil::gray_color_t{}), f_dst.min_v_);
        }

        // WHITE
        {
            pixel_src_t const src{f_src.min_v_};
            pixel_dst_t dst;
            gil::color_convert(src, dst);

            BOOST_TEST_EQ(gil::get_color(dst, gil::gray_color_t{}), f_dst.max_v_);
        }
    }

    static void run()
    {
        boost::mp11::mp_for_each
        <
            mp11::mp_list
            <
                gil::gray8_pixel_t,
                gil::gray8s_pixel_t,
                gil::gray16_pixel_t,
                gil::gray16s_pixel_t,
                gil::gray32_pixel_t,
                gil::gray32s_pixel_t,
                gil::gray32f_pixel_t
            >
        >(test_gray_from_cmyk<SrcPixel>{});
    }
};

int main() 
{
    test_rgb_from_gray<gil::gray8_pixel_t>::run();
    test_rgb_from_gray<gil::gray8s_pixel_t>::run();
    test_rgb_from_gray<gil::gray16_pixel_t>::run();
    test_rgb_from_gray<gil::gray16s_pixel_t>::run();
    test_rgb_from_gray<gil::gray32_pixel_t>::run();
    test_rgb_from_gray<gil::gray32s_pixel_t>::run();
    test_rgb_from_gray<gil::gray32f_pixel_t>::run();

    test_rgb_from_cmyk::run();
    
    test_gray_from_rgb<gil::rgb8_pixel_t>::run();
    test_gray_from_rgb<gil::rgb8s_pixel_t>::run();
    test_gray_from_rgb<gil::rgb16_pixel_t>::run();
    test_gray_from_rgb<gil::rgb16s_pixel_t>::run();
    test_gray_from_rgb<gil::rgb32_pixel_t>::run();
    test_gray_from_rgb<gil::rgb32s_pixel_t>::run();
    test_gray_from_rgb<gil::rgb32f_pixel_t>::run();

    test_gray_from_cmyk<gil::cmyk8_pixel_t>::run();
    test_gray_from_cmyk<gil::cmyk16_pixel_t>::run();
    test_gray_from_cmyk<gil::cmyk32_pixel_t>::run();
    test_gray_from_cmyk<gil::cmyk32f_pixel_t>::run();
    
    return ::boost::report_errors();
}
