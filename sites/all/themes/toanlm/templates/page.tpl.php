<style>
    body {
        background-color: <?php print theme_get_setting('bg_body', 'toanlm'); ?>;
    }
</style>
<div class="main-wrap">
<header id="header">
    <div class="logo"> 
        <?php //krumo($logo);?>
        <img src="<?php print $logo;?>" alt="<?php print $site_name; ?>" title="<?php print $site_name; ?>" />
    </div>
     <?php 
        $social_display = theme_get_setting('social_display', 'toanlm');
        if($social_display) :
        $google_url = theme_get_setting('google_url', 'toanlm');
     ?>        
        <div class="social">
            <?php print $google_url;?>
        </div>
    <?php endif; ?>
</header>
<?php if($page['main_menu']) : ?>
    <div class="navigation">
        <?php print render($page['main_menu']); ?>  
    </div>
<?php endif; ?>
<?php if($page['highlighted']) : ?>
    <div class="slidershow">
        <?php print render($page['highlighted']); ?>
    </div>
<?php endif;?>

<div class="content">
    <?php if($page['sidebar_first']) : ?>
        <div class="left-page">
            <?php print render($page['sidebar_first']); ?>
        </div> 
    <?php endif;?>
    <div class="content-page">
        <?php print render($page['content']); ?>
    </div>     
</div>

<footer id="footer">
    <?php print $feed_icons; ?>
</footer>
</div>